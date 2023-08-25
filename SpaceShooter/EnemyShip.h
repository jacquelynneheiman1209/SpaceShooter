#pragma once
#include <SFML/Graphics.hpp>

#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

class EnemyShip
{
public:
	EnemyShip();

	bool initialize();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

};

#endif // !ENEMY_SHIP_H



