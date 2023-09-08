#include "GameScene.h"
#include "Debug.h"

GameScene::GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds) : player(sf::Vector2f(640, 360), gameBounds), pauseMenu(), gameOverMenu(), playerHUD(gameBounds), confirmationMenu(), optionsMenu()
{
	this->sceneLoader = sceneLoader;
	this->gameBounds = gameBounds;
}

bool GameScene::initialize(sf::FloatRect windowBounds)
{
	gameBounds = windowBounds;

	showPauseMenu = false;
	showConfirmationMenu = false;
	showOptionsMenu = false;

	confirmationReason = "";

	// reset game over & pause settings
	isGameOver = false;
	isPaused = false;

	// reset asteroids
	numAsteroidsInPool = 10;
	numAsteroidsAllowedInScene = 3;
	numAsteroidsSpawned = 0;

	// reset enemies
	numEnemiesInPool = 5;
	numEnemiesAllowedInScene = 1;
	numEnemiesShipsSpawned = 0;

	ScoreManager::setScore(0);

	// reset difficulty modifiers
	difficultyScoreThreshold = 500;
	scoreThresholdIncreasePerDifficulty = 500;
	difficultyLevel = 0;

	// create new game objects
	player = Player(sf::Vector2f(gameBounds.left + (gameBounds.width / 2), gameBounds.top + (gameBounds.height / 2)), gameBounds);
	pauseMenu = PauseMenu();
	gameOverMenu = GameOverMenu();

	if (!gameOverMenu.initialize(gameBounds))
	{
		return false;
	}

	playerHUD = PlayerHUD(gameBounds);

	confirmationMenu = ConfirmationMenu();

	if (!confirmationMenu.initialize(gameBounds))
	{
		return false;
	}

	optionsMenu = OptionsMenu();

	if (!optionsMenu.initialize(gameBounds))
	{

	}

	// initialize game objects
	if (!playerHUD.initialize(gameBounds))
	{
		return false;
	}

	if (!player.initialize())
	{
		return false;
	}

	if (!initializeAsteroids())
	{
		return false;
	}

	if (!initializeEnemyShips())
	{
		return false;
	}

	if (!pauseMenu.initialize(windowBounds))
	{
		return false;
	}

	return true;
}

void GameScene::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (!isGameOver)
	{
		if (event->type == event->KeyPressed)
		{
			if (event->key.code == sf::Keyboard::Escape)
			{
				if (isPaused)
				{
					unpauseGame();
				}
				else
				{
					pauseGame();
				}
			}
		}

		if (isPaused)
		{
			if (showPauseMenu)
			{
				if (event->type == event->MouseButtonPressed)
				{
					if (pauseMenu.continueGameButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						isPaused = false;
						showPauseMenu = false;
						showConfirmationMenu = false;
						pauseMenu.continueGameButton.click();
					}

					if (pauseMenu.restartLevelButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						pauseMenu.restartLevelButton.click();
						showPauseMenu = false;
						showConfirmationMenu = true;
						confirmationReason = "Restart";
					}

					if (pauseMenu.optionsButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						pauseMenu.optionsButton.click();
						showPauseMenu = false;
						showOptionsMenu = true;
					}

					if (pauseMenu.menuButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						pauseMenu.menuButton.click();
						showPauseMenu = false;
						showConfirmationMenu = true;
						confirmationReason = "Main Menu";
					}
				}

				pauseMenu.handleInput(window, event);
			}

			if (showConfirmationMenu)
			{
				if (event->type == event->MouseButtonPressed)
				{
					if (confirmationMenu.yesButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						if (confirmationReason == "Restart")
						{
							confirmationMenu.yesButton.click();
							initialize(gameBounds);
						}
						else if (confirmationReason == "Main Menu")
						{
							confirmationMenu.yesButton.click();
							sceneLoader->loadScene("Main Menu", gameBounds);
						}
					}

					if (confirmationMenu.noButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						confirmationMenu.noButton.click();
						showPauseMenu = true;
						showConfirmationMenu = false;
					}
				}

				confirmationMenu.handleInput(window, event);
			}

			if (showOptionsMenu)
			{
				if (event->type == sf::Event::MouseButtonPressed)
				{
					if (optionsMenu.closeButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						optionsMenu.closeButton.click();
						showPauseMenu = true;
						showOptionsMenu = false;
					}

					if (optionsMenu.saveButton.isClicked(sf::Mouse::getPosition(*window)))
					{
						SaveManager::Save();
						optionsMenu.saveButton.click();
						showPauseMenu = true;
						showOptionsMenu = false;
					}
				}

				optionsMenu.handleInput(window, event);
			}
		}
		else
		{
			player.handleInput(window, event);
			playerHUD.handleInput(window, event);
		}
	}
	else
	{
		gameOverMenu.handleInput(window, event);

		if (event->type == event->MouseButtonPressed)
		{
			if (gameOverMenu.playAgainButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				gameOverMenu.playAgainButton.click();
				initialize(gameBounds);
			}

			if (gameOverMenu.mainMenuButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				gameOverMenu.mainMenuButton.click();
				sceneLoader->loadScene("Main Menu", gameBounds);
			}
		}
	}
}

void GameScene::update(float deltaTime)
{
	if (!isGameOver)
	{
		if (!isPaused)
		{
			player.update(deltaTime);
			playerHUD.update(deltaTime, player.getLives(), ScoreManager::getScore());

			for (int i = 0; i < enemyShips.size(); i++)
			{
				enemyShips[i].get()->update(deltaTime, player.getPosition());

				if (enemyShips[i].get()->isActive && !enemyShips[i].get()->isInGameBounds)
				{
					enemyShips[i].get()->destroy();
					numEnemiesShipsSpawned--;
				}
			}

			for (int i = 0; i < asteroids.size(); i++)
			{
				asteroids[i].get()->update(deltaTime);

				if (asteroids[i].get()->isActive && !asteroids[i].get()->isInGameBounds)
				{
					asteroids[i].get()->destroy();
					numAsteroidsSpawned--;
				}
			}

			if (!canSpawnAsteroid)
			{
				if (asteroidSpawnTimer < asteroidSpawnDelay)
				{
					asteroidSpawnTimer += deltaTime;
				}

				if (asteroidSpawnTimer >= asteroidSpawnDelay && numAsteroidsSpawned < numAsteroidsAllowedInScene)
				{
					canSpawnAsteroid = true;
				}
			}
			else
			{
				spawnAsteroid();
			}

			if (!canSpawnEnemy)
			{
				if (enemySpawnTimer < enemySpawnDelay)
				{
					enemySpawnTimer += deltaTime;
				}

				if (enemySpawnTimer >= enemySpawnDelay && numEnemiesShipsSpawned < numEnemiesAllowedInScene)
				{
					canSpawnEnemy = true;
				}
			}
			else
			{
				spawnEnemy();
			}

			// check collisions on the player bullets
			auto playerBullets = player.getBullets();

			for (int i = 0; i < playerBullets.size(); i++)
			{
				if (playerBullets[i]->isActive)
				{
					// check for player bullet collision with asteroids
					for (int a = 0; a < asteroids.size(); a++)
					{
						if (asteroids[a].get()->isActive)
						{
							if (playerBullets[i]->getCollider().intersects(asteroids[a].get()->getCollider()))
							{
								asteroids[a].get()->destroy();
								playerBullets[i]->destroy();

								addScore(asteroidPoints);
								numAsteroidsSpawned--;
							}
						}
					}

					// check for player bullet collision with enemy ships
					for (int e = 0; e < enemyShips.size(); e++)
					{
						if (enemyShips[e].get()->isActive)
						{
							if (playerBullets[i]->getCollider().intersects(enemyShips[e].get()->getCollider()))
							{
								enemyShips[e].get()->destroy();
								playerBullets[i]->destroy();

								addScore(enemyPoints);
								numEnemiesShipsSpawned--;
							}
						}
					}
				}
			}

			// check collisions on the asteroids with the player
			for (int i = 0; i < asteroids.size(); i++)
			{
				if (asteroids[i].get()->isActive)
				{
					if (asteroids[i].get()->getCollider().intersects(player.getCollider()))
					{
						player.loseLife();
						asteroids[i].get()->destroy();
						numAsteroidsSpawned--;
					}
				}
			}

			// check for collisions on the enemy ships with the player
			for (int i = 0; i < enemyShips.size(); i++)
			{
				if (enemyShips[i].get()->isActive)
				{
					if (enemyShips[i].get()->getCollider().intersects(player.getCollider()))
					{
						player.loseLife();
						enemyShips[i].get()->destroy();
						numEnemiesShipsSpawned--;
					}
				}
			}

			// check for game over
			if (player.getLives() <= 0)
			{
				isGameOver = true;
			}
		}
	}
}

void GameScene::draw(sf::RenderWindow* window)
{
	if (!isGameOver)
	{
		player.draw(window);
		playerHUD.draw(window);

		for (int i = 0; i < asteroids.size(); i++)
		{
			asteroids[i].get()->draw(window);
		}

		for (int i = 0; i < enemyShips.size(); i++)
		{
			enemyShips[i].get()->draw(window);
		}

		if (isPaused)
		{
			if (showPauseMenu)
			{
				pauseMenu.draw(window);
			}

			if (showConfirmationMenu)
			{
				confirmationMenu.draw(window);
			}

			if (showOptionsMenu)
			{
				optionsMenu.draw(window);
			}
		}
	}
	else
	{
		gameOverMenu.draw(window);
	}
}

void GameScene::handleWindowResize(sf::FloatRect newWindowSize)
{
	if (!isPaused)
	{
		isPaused = true;
	}

	playerHUD = PlayerHUD(newWindowSize);
	pauseMenu = PauseMenu();
	gameOverMenu = GameOverMenu();

	player = Player(sf::Vector2f(newWindowSize.left + (newWindowSize.width / 2), newWindowSize.top + (newWindowSize.height / 2)), newWindowSize);  

	player.initialize();
	playerHUD.initialize(newWindowSize);
	pauseMenu.initialize(newWindowSize);
	gameOverMenu.initialize(newWindowSize);

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].get()->reposition(newWindowSize);
	}

	for (int i = 0; i < enemyShips.size(); i++)
	{
		enemyShips[i].get()->reposition(newWindowSize);
	}

	gameBounds = newWindowSize;
}

bool GameScene::initializeAsteroids()
{
	asteroids.clear();

	for (int i = 0; i < numAsteroidsInPool; i++)
	{
		std::unique_ptr<Asteroid> asteroid = std::unique_ptr<Asteroid>(new Asteroid());
		
		if (!asteroid.get()->initialize())
		{
			Debug::Log("GameScene.cpp : Could not load asteroid " + std::to_string(i));
			return false;
		}
		
		asteroids.push_back(std::move(asteroid));
	}

	return true;
}

bool GameScene::initializeEnemyShips()
{
	enemyShips.clear();

	for (int i = 0; i < numEnemiesInPool; i++)
	{
		std::unique_ptr<EnemyShip> enemyShip = std::unique_ptr<EnemyShip>(new EnemyShip());

		if (!enemyShip.get()->initialize())
		{
			Debug::Log("GameScene.cpp : Could not load enemyShip " + std::to_string(i));
			return false;
		}

		enemyShips.push_back(std::move(enemyShip));
	}

	return true;
}

int GameScene::getNextAsteroidIndex()
{
	int nextAsteroidIndex = -1;

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (!asteroids[i].get()->isActive && asteroids[i].get()->isAtInactivePosition)
		{
			nextAsteroidIndex = i;
			break;
		}
	}

	return nextAsteroidIndex;
}

int GameScene::getNextEnemyShipIndex()
{
	int nextEnemyIndex = -1;

	for (int i = 0; i < enemyShips.size(); i++)
	{
		if (!enemyShips[i].get()->isActive && enemyShips[i].get()->isAtInactivePosition)
		{
			nextEnemyIndex = i;
			break;
		}
	}

	return nextEnemyIndex;
}

void GameScene::increaseDifficulty()
{
	int randIncrease = rand() % 3;

	if (randIncrease == 0)
	{
		// increase number of asteroids allowed in the scene
		numAsteroidsAllowedInScene++;

		if (numAsteroidsSpawned < numAsteroidsAllowedInScene)
		{
			spawnAsteroid();
		}
	}
	else if (randIncrease == 1)
	{
		// increase the number of enemies allowed in the scene
		numEnemiesAllowedInScene++;
	}
	else if (randIncrease == 2)
	{
		// increase asteroid speed
		for (int i = 0; i < asteroids.size(); i++)
		{
			int randSpeedIncrease = (rand() % 5) + 1;
			asteroids[i].get()->increaseSpeed(randSpeedIncrease);
		}
	}

	difficultyLevel++;
	difficultyScoreThreshold += scoreThresholdIncreasePerDifficulty;
	scoreThresholdIncreasePerDifficulty += 1000;
}

void GameScene::addScore(int amountToAdd)
{
	int newScore = ScoreManager::getScore() + amountToAdd;

	if (ScoreManager::getScore() < difficultyScoreThreshold && newScore >= difficultyScoreThreshold)
	{
		increaseDifficulty();
	}

	ScoreManager::setScore(newScore);

	if (newScore > ScoreManager::getHiScore())
	{
		ScoreManager::setHiScore(newScore);
	}
}

void GameScene::spawnAsteroid()
{
	int nextAsteroid = getNextAsteroidIndex();

	if (nextAsteroid >= 0)
	{
		asteroids[nextAsteroid].get()->spawn(player.getPosition(), gameBounds);
		numAsteroidsSpawned++;
	}

	canSpawnAsteroid = false;
	asteroidSpawnTimer = 0;
}

void GameScene::spawnEnemy()
{
	int nextEnemyShip = getNextEnemyShipIndex();

	if (nextEnemyShip >= 0)
	{
		enemyShips[nextEnemyShip].get()->spawn(player.getPosition(), gameBounds);
		numEnemiesShipsSpawned++;
	}

	canSpawnEnemy = false;

	// reset the spawn timer & select a random spawn delay
	enemySpawnTimer = 0;
	enemySpawnDelay = (rand() % static_cast<int>(maxEnemyShipSpawnDelay)) + minEnemyShipSpawnDelay;
}

void GameScene::pauseGame()
{
	isPaused = true;
	showPauseMenu = true;
	showConfirmationMenu = false;
	showOptionsMenu = false;
}

void GameScene::unpauseGame()
{
	isPaused = false;
	showPauseMenu = false;
	showConfirmationMenu = false;
	showOptionsMenu = false;
}
