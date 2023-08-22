#include "SceneManager.h"

SceneManager::SceneManager()
{
}

bool SceneManager::initialize()
{
	scenes["Game"] = Scene();
	return true;
}

void SceneManager::update(float deltaTime)
{
	for (auto keyValuePair = scenes.begin(); keyValuePair != scenes.end(); keyValuePair++)
	{
		keyValuePair->second.update(deltaTime);
	}
}

void SceneManager::draw(sf::RenderWindow* window)
{
	for (auto keyValuePair = scenes.begin(); keyValuePair != scenes.end(); keyValuePair++)
	{
		keyValuePair->second.draw(window);
	}
}

void SceneManager::loadScene(std::string sceneName)
{
	currentScene = sceneName;
	scenes[currentScene].initialize();
}

Scene* SceneManager::getScene(std::string sceneName)
{
	if (scenes.find(sceneName) != scenes.end())
	{
		return &scenes[sceneName];
	}
	
	return nullptr;
}

