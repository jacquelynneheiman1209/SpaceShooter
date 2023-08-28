#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"

#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

class EnemyShip : public Enemy
{
public:
	EnemyShip();

protected:
	void move(float deltaTime, sf::Vector2f targetPosition) override;

};

#endif // !ENEMY_SHIP_H




