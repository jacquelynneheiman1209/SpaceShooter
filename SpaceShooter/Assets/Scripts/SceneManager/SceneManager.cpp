#include "SceneManager.h"
#include <assert.h>
#include <iostream>

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager() : mainMenuScene(this), gameScene(this)
{
	assert(instance == nullptr);
	instance = this;
}

bool SceneManager::initialize()
{
	mainMenuScene = MainMenuScene(this);
	gameScene = GameScene(this);

	currentScene = "Main Menu";

	if (!mainMenuScene.initialize())
	{
		return false;
	}

	return true;
}

void SceneManager::update(float deltaTime)
{
	if (currentScene == "Main Menu")
	{
		mainMenuScene.update(deltaTime);
	}
	else if (currentScene == "Game")
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

