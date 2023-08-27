#include "SceneManager.h"
#include <assert.h>
#include <iostream>

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager() : mainMenuScene(this, gameBounds), gameScene(this, gameBounds)
{
	assert(instance == nullptr);
	instance = this;
}

bool SceneManager::initialize(sf::FloatRect gameBounds)
{
	this->gameBounds = gameBounds;
	mainMenuScene = MainMenuScene(this, gameBounds);
	gameScene = GameScene(this, gameBounds);

	currentScene = "Main Menu";

	if (!mainMenuScene.initialize(gameBounds))
	{
		return false;
	}

	return true;
}

void SceneManager::update(float deltaTime)
{
	if (currentScene == "Game")
	{
		gameScene.update(deltaTime);
	}
}

void SceneManager::draw(sf::RenderWindow* window)
{
	if (currentScene == "Main Menu")
	{
		mainMenuScene.draw(window);
	}
	else if (currentScene == "Game")
	{
		gameScene.draw(window);
	}
}

void SceneManager::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (currentScene == "Main Menu")
	{
		mainMenuScene.handleInput(window, event);
	}
	else if (currentScene == "Game")
	{
		gameScene.handleInput(window, event);
	}
}

void SceneManager::handleWindowResize(sf::FloatRect newWindowSize)
{
	if (currentScene == "Main Menu")
	{
		mainMenuScene.handleWindowResize(newWindowSize);
	}
	else if (currentScene == "Game")
	{
		gameScene.handleWindowResize(newWindowSize);
	}
}

