#pragma once
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(sf::Vector2f startPosition, sf::FloatRect levelBounds);

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	int getLives();

private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	sf::Vector2f startPosition;
	sf::Vector2f playerScale = sf::Vector2f(0.5f, 0.5f);

	sf::FloatRect levelBounds;

	float moveSpeed = 300;
	float rotateSpeed = 100;

	bool moveForwards = false;
	bool moveBackwards = false;
	bool rotateLeft = false;
	bool rotateRight = false;
	bool shoot = false;

	bool isDead = false;

	int lives = 3;

	void move(float deltaTime);
	void rotate(float deltaTime);
	void loseLife();
	void resetPosition();
};

#endif // !PLAYER_H


