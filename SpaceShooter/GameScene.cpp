#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds) : player(sf::Vector2f(640, 360), gameBounds), pauseMenu(), gameOverMenu(), playerHUD(gameBounds)
{
	this->sceneLoader = sceneLoader;
	this->gameBounds = gameBounds;
}

bool GameScene::initialize()
{
	isGameOver = false;
	isPaused = false;

	player = Player(sf::Vector2f(640, 360), gameBounds);

	pauseMenu = PauseMenu();
	gameOverMenu = GameOverMenu();
	playerHUD = PlayerHUD(gameBounds);

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
					asteroidSpawnTimer++;
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
					canSpawnAsteroid = false;
					asteroidSpawnTimer = 0;
				}
			}

			// check collisions on the player bullets
			auto playerBullets = player.getBullets();

			for (int i = 0; i < playerBullets.size(); i++)
			{
				for (int a = 0; a < asteroids.size(); a++)
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

	asteroids[0].get()->spawn(player.getPosition(), gameBounds);

	return true;
}

int GameScene::getNextAsteroidIndex()
{
	int nextAsteroid = -1;

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (!asteroids[i].get()->isActive && asteroids[i].get()->isAtInactivePosition)
		{
			nextAsteroid = i;
			break;
		}
	}

	return nextAsteroid;
}
