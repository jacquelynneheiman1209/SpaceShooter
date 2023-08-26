#include "EnemyShip.h"
#include <iostream>


EnemyShip::EnemyShip(sf::FloatRect gameBounds)
{
}

bool EnemyShip::initialize()
{
	int randomEnemy = rand() % static_cast<int>(textures.size());
	
	if (!enemyTexture.loadFromFile(textures[randomEnemy]))
	{
		std::cout << "EnemyShip.cpp : Could not load 'enemyTexture' from " << textures[randomEnemy] << std::endl;
		return false;
	}

	return true;
}

void EnemyShip::update(float deltaTime)
{
}

void EnemyShip::draw(sf::RenderWindow* window)
{
}

void EnemyShip::spawn(sf::Vector2f position, sf::Vector2f targetPosition)
{
}

void EnemyShip::destroy()
{
}
