#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneLoader* sceneLoader) : player(sf::Vector2f(640, 360))
{
	this->sceneLoader = sceneLoader;
	isPaused = false;
}

bool GameScene::initialize()
{
	isPaused = false;
	player = Player(sf::Vector2f(640, 360));

	if (!player.initialize())
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
			isPaused = true;
			// open pause menu
		}
	}

	player.handleInput(window, event);
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
}
