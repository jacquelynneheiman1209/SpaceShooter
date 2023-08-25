#pragma once
#include <SFML/Graphics.hpp>

#ifndef BULLET_H
#define BULLET_H

class Bullet
{
public:
	bool isActive = false;

	Bullet(sf::FloatRect levelBounds);

	bool initialize();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void spawn(sf::Vector2f position, float rotation);
	void destroy();

private:
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;

	sf::Vector2f inactivePosition = sf::Vector2f(-1000, -1000);

	sf::FloatRect levelBounds;

	float destroyTimer = 0;
	float destroyDelay = 10;

	float moveSpeed = 600;

};

#endif // !BULLET_H



