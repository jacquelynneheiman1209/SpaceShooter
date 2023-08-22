#pragma once
#include <SFML/Graphics.hpp>
#include "Scenes/Scene.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager
{
public:
	SceneManager();

	bool initialize();
	void update(float delatTime);
	void draw(sf::RenderWindow* window);

	void loadScene(std::string sceneName);
	Scene* getScene(std::string sceneName);

private:
	std::string currentScene;
	std::map<std::string, Scene> scenes;

	void addScene(std::string sceneName);

};

#endif // !SCENE_MANAGER_H



