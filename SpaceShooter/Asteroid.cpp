#include "Asteroid.h"
#include "Debug.h"

Asteroid::Asteroid() : Enemy()
{
	textures = std::vector<std::string>{
		"Assets/Graphics/Meteors/meteorBrown_big1.png",
		"Assets/Graphics/Meteors/meteorBrown_big2.png",
		"Assets/Graphics/Meteors/meteorBrown_big3.png",
		"Assets/Graphics/Meteors/meteorBrown_big4.png",
		"Assets/Graphics/Meteors/meteorBrown_med1.png",
		"Assets/Graphics/Meteors/meteorBrown_med2.png",
	};

	minMoveSpeed = 25;
	maxMoveSpeed = 50;

	moveSpeed = 25;
}

void Asteroid::spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds)
{
	Enemy::spawn(targetPosition, gameBounds);

	// get the direction to the player
	moveDirection = targetPosition - sprite.getPosition();

	// Normalizing the moveDirection vector
	float magnitude = sqrt((moveDirection.x * moveDirection.x) + (moveDirection.y * moveDirection.y));
	moveDirection /= magnitude;
}

void Asteroid::increaseSpeed(float amount)
{
	moveSpeed += amount;
}

void Asteroid::move(float deltaTime, sf::Vector2f playerPosition)
{
	sf::Vector2f currentPosition = sprite.getPosition();
	currentPosition.x += moveDirection.x * moveSpeed * deltaTime;
	currentPosition.y += moveDirection.y * moveSpeed * deltaTime;

	isInGameBounds = isInBounds();

	sprite.setPosition(currentPosition);

	setActive();
}
