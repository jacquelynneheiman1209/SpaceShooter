#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds) : player(sf::Vector2f(640, 360), gameBounds), pauseMenu(), gameOverMenu(), hud()
{
	this->sceneLoader = sceneLoader;
	this->gameBounds = gameBounds;
}

bool GameScene::initialize()
{
	isGameOver = false;
	isPaused = false;

	enemiesKilled = 0;

	player = Player(sf::Vector2f(640, 360), gameBounds);

	pauseMenu = PauseMenu();
	gameOverMenu = GameOverMenu();
	hud = GameHUD();

	if (!player.initialize())
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

	std::cout << "Player Lives: " << player.getLives() << std::endl;

	if (!hud.initialize(player.getLives()))
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

			if (event->key.code == sf::Keyboard::Tab)
			{
				enemiesKilled++;

				if (enemiesKilled >= numberEmeniesToKill)
				{
					isGameOver = true;
				}
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
		}
	}
}

void GameScene::draw(sf::RenderWindow* window)
{
	if (!isGameOver)
	{
		player.draw(window);
		hud.draw(window, player.getLives());

		if (isPaused)
		{
			pauseMenu.draw(window);
		}
	}
	else
	{
		gameOverMenu.draw(window);
	}
}
