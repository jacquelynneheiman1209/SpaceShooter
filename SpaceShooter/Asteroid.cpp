#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid()
{
}

bool Asteroid::initialize()
{
	srand(time(0));

	int randAsteroidIndex = rand() % textures.size();

	if (!asteroidTexture.loadFromFile(textures[randAsteroidIndex]))
	{
		std::cout << "Asteroid.cpp : Could not load 'asteroidTexture' from 'Assets/Graphics/Meteors/meteorBrown_big1.png'" << std::endl;
		return false;
	}

	asteroidSprite.setTexture(asteroidTexture);

	sf::FloatRect asteroidBounds = asteroidSprite.getLocalBounds();

	sf::Vector2f origin;
	origin.x = asteroidBounds.left + (asteroidBounds.width / 2);
	origin.y = asteroidBounds.top + (asteroidBounds.height / 2);

	asteroidSprite.setOrigin(origin);
	asteroidSprite.setPosition(inactivePosition);

	return true;
}

void Asteroid::update(float deltaTime)
{
	if (isActive || (!isActive && asteroidSprite.getPosition() != inactivePosition))
	{
		std::cout << "Sprite Position: " << asteroidSprite.getPosition().x << ", " << asteroidSprite.getPosition().y << std::endl;
	}

	if (isActive)
	{
		move(deltaTime);
	}
	else
	{
		if (asteroidSprite.getPosition() != inactivePosition)
		{
			move(deltaTime);
		}
	}
}

void Asteroid::draw(sf::RenderWindow* window)
{
	window->draw(asteroidSprite);
}

void Asteroid::spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds)
{
	this->gameBounds = gameBounds;

	srand(time(0));

	// choose a random edge of the screen
	ScreenEdge randomScreenEdge = static_cast<ScreenEdge>(rand() % 4);

	sf::Vector2f spawnPosition;

	if (randomScreenEdge == ScreenEdge::LEFT)
	{
		std::cout << "Spawn on LEFT side of screen..." << std::endl;
		spawnPosition.x = gameBounds.left - 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::RIGHT)
	{
		std::cout << "Spawn on RIGHT side of screen..." << std::endl;
		spawnPosition.x = (gameBounds.left + gameBounds.width) + 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::TOP)
	{
		std::cout << "Spawn on TOP side of screen..." << std::endl;
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = gameBounds.top - 200;
	}

	if (randomScreenEdge == ScreenEdge::BOTTOM)
	{
		std::cout << "Spawn on BOTTOM side of screen..." << std::endl;
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = (gameBounds.top + gameBounds.height) + 200;
	}

	asteroidSprite.setPosition(spawnPosition);
	this->targetPosition = targetPosition - asteroidSprite.getPosition();

	std::cout << "Spawn Position: " << asteroidSprite.getPosition().x << ", " << asteroidSprite.getPosition().y << std::endl;
	std::cout << "Direction To Target: " << targetPosition.x << ", " << targetPosition.y << std::endl;
}

void Asteroid::destroy()
{
	isActive = false;
	asteroidSprite.setPosition(inactivePosition);
}

void Asteroid::move(float deltaTime)
{
	// TODO : Get the asteroid moving towards the player

	float dx = asteroidSprite.getPosition().x - targetPosition.x;
	float dy = asteroidSprite.getPosition().y - targetPosition.y;

	float rotation = (atan2(dy, dx)) * 180 / 3.14159265;

	sf::Vector2f currentPosition = asteroidSprite.getPosition();
	currentPosition.x += static_cast<float>(cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
	currentPosition.y += static_cast<float>(sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);

	bool isInBoundsX = (currentPosition.x > gameBounds.left && currentPosition.x < (gameBounds.left + gameBounds.width));
	bool isInBoundsY = (currentPosition.y > gameBounds.top && currentPosition.y < (gameBounds.top + gameBounds.height));

	asteroidSprite.setPosition(currentPosition);

	if (isActive)
	{
		if (!isInBoundsX || !isInBoundsY)
		{
			destroy();
		}
	}
	else
	{
		if ((asteroidSprite.getPosition() != inactivePosition) && (isInBoundsX && isInBoundsY))
		{
			isActive = true;
		}
	}
}
