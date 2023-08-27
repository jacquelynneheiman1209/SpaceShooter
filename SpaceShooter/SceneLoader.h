#pragma once
#include <string>

#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

class SceneLoader
{
public:
	virtual void loadScene(std::string sceneName, sf::FloatRect windowSize) = 0;
};

#endif // !SCENE_LOADER_H



