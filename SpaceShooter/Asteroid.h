#pragma once
#include <SFML/Graphics.hpp>

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid
{
public:
	enum ScreenEdge { LEFT, TOP, RIGHT, BOTTOM };
	Asteroid();

	bool initialize();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds);
	void destroy();

private:
	std::vector<std::string> textures {
		"Assets/Graphics/Meteors/meteorBrown_big1.png",
		"Assets/Graphics/Meteors/meteorBrown_big2.png",
		"Assets/Graphics/Meteors/meteorBrown_big3.png",
		"Assets/Graphics/Meteors/meteorBrown_big4.png",
		"Assets/Graphics/Meteors/meteorBrown_med1.png",
		"Assets/Graphics/Meteors/meteorBrown_med2.png",
	};

	sf::Texture asteroidTexture;
	sf::Sprite asteroidSprite;

	bool isActive = false;
	bool isInGameBounds = false;

	sf::Vector2f inactivePosition = sf::Vector2f(-1000, -1000);
	sf::Vector2f targetPosition;

	float moveSpeed = 100;

	sf::FloatRect gameBounds;

	void move(float deltaTime);

};

#endif // !ASTEROID_H



