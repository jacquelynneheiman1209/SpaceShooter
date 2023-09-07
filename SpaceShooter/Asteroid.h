#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid : public Enemy
{
public:
	Asteroid();

	void spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds) override;
	void increaseSpeed(int amount);

protected:
	sf::Vector2f moveDirection;

	void move(float deltaTime, sf::Vector2f playerPosition) override;

};

#endif // !ASTEROID_H



