#pragma once
#include <SFML/Graphics.hpp>
#include "SceneLoader.h"
#include "MainMenuScene.h"
#include "GameScene.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager : public SceneLoader
{
public:
	SceneManager();

	bool initialize(sf::FloatRect gameBounds);
	void update(float delatTime);
	void draw(sf::RenderWindow* window);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void handleWindowResize(sf::FloatRect newWindowSize);

	void SceneLoader::loadScene(std::string sceneName, sf::FloatRect windowSize)
	{
		currentScene = sceneName;

		if (currentScene == "Main Menu")
		{
			mainMenuScene.initialize(windowSize);
		}
		else if (currentScene == "Game")
		{
			gameScene.initialize(windowSize);
		}
	}

private:
	static SceneManager* instance;
	std::string currentScene;

	MainMenuScene mainMenuScene;
	GameScene gameScene;

	sf::FloatRect gameBounds;
};

#endif // !SCENE_MANAGER_H



