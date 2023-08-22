#pragma once
#include <SFML/Graphics.hpp>

#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene();

	bool initialize();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:

};

#endif // !SCENE_H



