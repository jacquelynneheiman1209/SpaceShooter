#pragma once
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(sf::Vector2f startPosition);

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	sf::Vector2f startPosition;
	sf::Vector2f playerScale = sf::Vector2f(0.5f, 0.5f);

	float moveSpeed = 300;
	float rotateSpeed = 100;

	bool moveForwards = false;
	bool moveBackwards = false;
	bool rotateLeft = false;
	bool rotateRight = false;
	bool shoot = false;

	void move(float deltaTime);
	void rotate(float deltaTime);
};

#endif // !PLAYER_H


