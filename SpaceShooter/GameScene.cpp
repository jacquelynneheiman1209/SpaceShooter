#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds) : player(sf::Vector2f(640, 360), gameBounds), pauseMenu(), gameOverMenu(), playerHUD(gameBounds)
{
	this->sceneLoader = sceneLoader;
	this->gameBounds = gameBounds;
}

bool GameScene::initialize()
{
	// reset game over & pause settings
	isGameOver = false;
	isPaused = false;

	// reset asteroids
	numAsteroidsAllowedInScene = 3;
	numAsteroidsSpawned = 0;

	// reset enemies
	numEnemiesAllowedInScene = 1;
	numEnemiesShipsSpawned = 0;

	// reset score
	score = 0;

	// create new game objects
	player = Player(sf::Vector2f(640, 360), gameBounds);
	pauseMenu = PauseMenu();
	gameOverMenu = GameOverMenu();
	playerHUD = PlayerHUD(gameBounds);

	// initialize game objects
	if (!playerHUD.initialize())
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

	if (!pauseMenu.initialize())
	{
		return false;
	}

	if (!gameOverMenu.initialize())
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
				isPaused = !isPaused;
			}
		}

		if (isPaused)
		{
			if (event->type == event->MouseButtonPressed)
			{
				if (pauseMenu.continueGameButton.isClicked(sf::Mouse::getPosition(*window)))
				{
					isPaused = false;
				}

				if (pauseMenu.restartLevelButton.isClicked(sf::Mouse::getPosition(*window)))
				{
					initialize();
				}

				if (pauseMenu.optionsButton.isClicked(sf::Mouse::getPosition(*window)))
				{

				}

				if (pauseMenu.quitButton.isClicked(sf::Mouse::getPosition(*window)))
				{
					window->close();
				}
			}

			pauseMenu.handleInput(window, event);
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
				initialize();
			}

			if (gameOverMenu.mainMenuButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				sceneLoader->loadScene("Main Menu");
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
			playerHUD.update(deltaTime, player.getLives(), score);

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
				int nextAsteroid = getNextAsteroidIndex();

				if (nextAsteroid >= 0)
				{
					asteroids[nextAsteroid].get()->spawn(player.getPosition(), gameBounds);
					numAsteroidsSpawned++;
					
				}

				canSpawnAsteroid = false;
				asteroidSpawnTimer = 0;
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

								score += asteroidPoints;
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

								score += enemyPoints;
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
			pauseMenu.draw(window);
		}
	}
	else
	{
		gameOverMenu.draw(window, playerWon);
	}
}

bool GameScene::initializeAsteroids()
{
	asteroids.clear();

	for (int i = 0; i < numAsteroidsAllowedInScene; i++)
	{
		std::unique_ptr<Asteroid> asteroid = std::unique_ptr<Asteroid>(new Asteroid());
		
		if (!asteroid.get()->initialize())
		{
			std::cout << "GameScene.cpp : Could not load asteroid " << i << std::endl;
			return false;
		}
		
		asteroids.push_back(std::move(asteroid));
	}

	return true;
}

bool GameScene::initializeEnemyShips()
{
	enemyShips.clear();

	for (int i = 0; i < numEnemiesAllowedInScene; i++)
	{
		std::unique_ptr<EnemyShip> enemyShip = std::unique_ptr<EnemyShip>(new EnemyShip());

		if (!enemyShip.get()->initialize())
		{
			std::cout << "GameScene.cpp : Could not load enemyShip " << i << std::endl;
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
