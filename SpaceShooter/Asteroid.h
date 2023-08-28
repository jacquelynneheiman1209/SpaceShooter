#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

	void increaseSpeed(float amount);
	void reposition(sf::FloatRect newGameBounds);
	
	sf::FloatRect getCollider();

	bool isActive = false;
	bool isInGameBounds = false;
	bool isAtInactivePosition = true;

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

	sf::Vector2f inactivePosition = sf::Vector2f(-1000, -1000);
	sf::Vector2f moveDirection;

	sf::SoundBuffer destroySoundBuffer;
	sf::Sound destroySound;

	int minMoveSpeed = 25;
	int maxMoveSpeed = 50;

	float moveSpeed = 25;

	sf::FloatRect gameBounds;

	void move(float deltaTime);

};

#endif // !ASTEROID_H



