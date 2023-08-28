#include "EnemyShip.h"
#include "Debug.h"


EnemyShip::EnemyShip() : Enemy()
{
	textures = std::vector<std::string>{
		"Assets/Graphics/Enemies/enemyBlack1.png",
		"Assets/Graphics/Enemies/enemyBlack2.png",
		"Assets/Graphics/Enemies/enemyBlack3.png",
		"Assets/Graphics/Enemies/enemyBlack4.png",
		"Assets/Graphics/Enemies/enemyBlack5.png",
		"Assets/Graphics/Enemies/enemyBlue2.png",
		"Assets/Graphics/Enemies/enemyBlue3.png",
		"Assets/Graphics/Enemies/enemyBlue4.png",
		"Assets/Graphics/Enemies/enemyBlue5.png",
		"Assets/Graphics/Enemies/enemyGreen1.png",
		"Assets/Graphics/Enemies/enemyGreen2.png",
		"Assets/Graphics/Enemies/enemyGreen3.png",
		"Assets/Graphics/Enemies/enemyGreen4.png",
		"Assets/Graphics/Enemies/enemyGreen5.png",
		"Assets/Graphics/Enemies/enemyRed1.png",
		"Assets/Graphics/Enemies/enemyRed2.png",
		"Assets/Graphics/Enemies/enemyRed3.png",
		"Assets/Graphics/Enemies/enemyRed4.png",
		"Assets/Graphics/Enemies/enemyRed5.png",
	};

	scale = sf::Vector2f(0.5f, 0.5f);

	minMoveSpeed = 75;
	maxMoveSpeed = 175;

	moveSpeed = 150;
}

void EnemyShip::move(float deltaTime, sf::Vector2f targetPosition)
{
	float dx = sprite.getPosition().x - targetPosition.x;
	float dy = sprite.getPosition().y - targetPosition.y;

	float rotation = ((atan2(dy, dx)) * 180 / 3.14159265) + 90;

	sf::Vector2f currentPosition = sprite.getPosition();
	currentPosition.x += static_cast<float>(cos((rotation + 90) * (3.14159265 / 180)) * moveSpeed * deltaTime);
	currentPosition.y += static_cast<float>(sin((rotation + 90) * (3.14159265 / 180)) * moveSpeed * deltaTime);

	isInGameBounds = isInBounds();

	sprite.setRotation(rotation);
	sprite.setPosition(currentPosition);

	setActive();
}
