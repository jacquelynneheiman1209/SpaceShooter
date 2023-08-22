#pragma once
#include <SFML/Graphics.hpp>

#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene();

	virtual bool initialize();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow* window);

private:

};

#endif // !SCENE_H



