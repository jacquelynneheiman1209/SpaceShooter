#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid()
{
}

bool Asteroid::initialize()
{
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

	if (asteroidSprite.getPosition() == inactivePosition)
	{
		isAtInactivePosition = true;
	}
	else
	{
		isAtInactivePosition = false;
	}
}

void Asteroid::draw(sf::RenderWindow* window)
{
	if (isActive)
	{
		window->draw(asteroidSprite);
	}
}

void Asteroid::spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds)
{
	this->gameBounds = gameBounds;

	ScreenEdge randomScreenEdge = static_cast<ScreenEdge>(rand() % 4);

	sf::Vector2f spawnPosition;

	if (randomScreenEdge == ScreenEdge::LEFT)
	{
		spawnPosition.x = gameBounds.left - 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::RIGHT)
	{
		spawnPosition.x = (gameBounds.left + gameBounds.width) + 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::TOP)
	{
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = gameBounds.top - 200;
	}

	if (randomScreenEdge == ScreenEdge::BOTTOM)
	{
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = (gameBounds.top + gameBounds.height) + 200;
	}

	asteroidSprite.setPosition(spawnPosition);
	moveDirection = targetPosition - asteroidSprite.getPosition();

	// Normalizing the moveDirection vector
	float magnitude = sqrt((moveDirection.x * moveDirection.x) + (moveDirection.y * moveDirection.y));
	moveDirection /= magnitude;
}

void Asteroid::destroy()
{
	isActive = false;
	asteroidSprite.setPosition(inactivePosition);
}

sf::FloatRect Asteroid::getCollider()
{
	return asteroidSprite.getGlobalBounds();
}

void Asteroid::move(float deltaTime)
{
	sf::Vector2f currentPosition = asteroidSprite.getPosition();
	currentPosition.x += moveDirection.x * moveSpeed * deltaTime;
	currentPosition.y += moveDirection.y * moveSpeed * deltaTime;

	bool isInBoundsX = (currentPosition.x > gameBounds.left && currentPosition.x < (gameBounds.left + gameBounds.width));
	bool isInBoundsY = (currentPosition.y > gameBounds.top && currentPosition.y < (gameBounds.top + gameBounds.height));

	isInGameBounds = isInBoundsX && isInBoundsY;

	asteroidSprite.setPosition(currentPosition);

	if (!isActive)
	{
		if ((asteroidSprite.getPosition() != inactivePosition) && (isInBoundsX && isInBoundsY))
		{
			isActive = true;
		}
	}
}
