#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneLoader* sceneLoader) : player(sf::Vector2f(640, 360)), pauseMenu()
{
	this->sceneLoader = sceneLoader;
	isPaused = false;
}

bool GameScene::initialize()
{
	isPaused = false;
	player = Player(sf::Vector2f(640, 360));
	pauseMenu = PauseMenu();

	if (!player.initialize())
	{
		return false;
	}

	if (!pauseMenu.initialize())
	{
		return false;
	}

	return true;
}

void GameScene::handleInput(sf::RenderWindow* window, sf::Event* event)
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
	}
}

void GameScene::update(float deltaTime)
{
	if (!isPaused)
	{
		player.update(deltaTime);
	}
}

void GameScene::draw(sf::RenderWindow* window)
{
	player.draw(window);

	if (isPaused)
	{
		pauseMenu.draw(window);
	}
}
