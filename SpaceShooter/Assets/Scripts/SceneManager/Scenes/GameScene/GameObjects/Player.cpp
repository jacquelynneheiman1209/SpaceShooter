#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f startPos)
{
	startPosition = startPos;
	std::cout << "Start Position: " << startPos.x << ", " << startPos.y << std::endl;
}

bool Player::initialize()
{
	if (!playerTexture.loadFromFile("Assets/Graphics/playerShip1_blue.png"))
	{
		std::cout << "Could not load player texture from file..." << std::endl;
		return false;
	}

	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(playerScale);
	playerSprite.setOrigin(playerSprite.getLocalBounds().left + (playerSprite.getLocalBounds().width / 2), playerSprite.getLocalBounds().top + (playerSprite.getLocalBounds().height / 2));
	playerSprite.setPosition(startPosition);

	return true;
}

void Player::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveForwards = true;
	}
	else
	{
		moveForwards = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveBackwards = true;
	}
	else
	{
		moveBackwards = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotateLeft = true;
	}
	else
	{
		rotateLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotateRight = true;
	}
	else
	{
		rotateRight = false;
	}

	if (event->type == event->KeyPressed)
	{
		if (event->key.code == sf::Keyboard::Space)
		{
			shoot = true;
		}
	}
}

void Player::update(float deltaTime)
{
	move(deltaTime);
	rotate(deltaTime);
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(playerSprite);
}

void Player::move(float deltaTime)
{
	sf::Vector2f currentPosition = playerSprite.getPosition();
	float rotation = playerSprite.getRotation() - 90;
	
	if (moveForwards)
	{
		currentPosition.x += cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime;
		currentPosition.y += sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime;
	}
	else if (moveBackwards)
	{
		currentPosition.x -= cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime;
		currentPosition.y -= sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime;
	}

	playerSprite.setPosition(currentPosition);
	
}

void Player::rotate(float deltaTime)
{
	float rotation = playerSprite.getRotation();

	if (rotateLeft)
	{
		rotation -= rotateSpeed * deltaTime;
	}
	else if (rotateRight)
	{
		rotation += rotateSpeed * deltaTime;
	}

	playerSprite.setRotation(rotation);
}
