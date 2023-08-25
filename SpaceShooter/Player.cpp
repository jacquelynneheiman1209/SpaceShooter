#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f startPos, sf::FloatRect levelBounds)
{
	startPosition = startPos;
	this->levelBounds = levelBounds;
}

bool Player::initialize()
{
	if (!playerTexture.loadFromFile("Assets/Graphics/playerShip1_blue.png"))
	{
		std::cout << "Player.cpp : Could not load 'playerTexture' from 'Assets/Graphics/playerShip1_blue.png'" << std::endl;
		return false;
	}

	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(playerScale);
	playerSprite.setOrigin(playerSprite.getLocalBounds().left + (playerSprite.getLocalBounds().width / 2), playerSprite.getLocalBounds().top + (playerSprite.getLocalBounds().height / 2));
	playerSprite.setPosition(startPosition);

	for (int i = 0; i < totalNumberOfBullets; i++)
	{
		std::unique_ptr<Bullet> bullet = std::unique_ptr<Bullet>(new Bullet(levelBounds));
		bullets.push_back(std::move(bullet));

		int bulletIndex = static_cast<int>(bullets.size() - 1);

		if (!bullets[bulletIndex].get()->initialize())
		{
			std::cout << "Player.cpp : Could not load bullet " + bulletIndex << std::endl;
			return false;
		}
	}

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
			shootBullet = true;
		}
	}
}

void Player::update(float deltaTime)
{
	move(deltaTime);
	rotate(deltaTime);
	shoot();

	sf::Vector2f playerPosition = playerSprite.getPosition();
	bool isOutOfBoundsX = (playerPosition.x <= levelBounds.left || playerPosition.x >= levelBounds.left + levelBounds.width);
	bool isOutOfBoundsY = (playerPosition.y <= levelBounds.top || playerPosition.y >= levelBounds.top + levelBounds.height);

	if (isOutOfBoundsX || isOutOfBoundsY)
	{
		loseLife();
		resetPosition();
	}

	if (!canShoot)
	{
		shootTimer += deltaTime;

		if (shootTimer >= shootDelaySeconds)
		{
			canShoot = true;
			shootTimer = 0;
		}
	}

	// Update the bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].get()->update(deltaTime);
	}
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(playerSprite);

	// Only draw the bullets that have been shot && are on screen
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].get()->draw(window);
	}
}

int Player::getLives()
{
	return lives;
}

void Player::move(float deltaTime)
{
	sf::Vector2f currentPosition = playerSprite.getPosition();
	float rotation = playerSprite.getRotation() - 90;
	
	if (moveForwards)
	{
		currentPosition.x += static_cast<float>(cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
		currentPosition.y += static_cast<float>(sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
	}
	else if (moveBackwards)
	{
		currentPosition.x -= static_cast<float>(cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
		currentPosition.y -= static_cast<float>(sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
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

void Player::shoot()
{
	if (shootBullet)
	{
		if (canShoot)
		{
			int nextBullet = getNextBulletIndex();

			if (nextBullet >= 0)
			{
				bullets[nextBullet].get()->spawn(playerSprite.getPosition(), playerSprite.getRotation());
				canShoot = false;
			}
		}

		shootBullet = false;
	}
}

void Player::loseLife()
{
	lives--;

	if (lives <= 0)
	{
		isDead = true;
	}

	resetPosition();
}

void Player::resetPosition()
{
	playerSprite.setPosition(sf::Vector2f(levelBounds.left + (levelBounds.width / 2), levelBounds.top + (levelBounds.height / 2)));
}

int Player::getNextBulletIndex()
{
	int nextBullet = -1;

	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].get()->isActive)
		{
			nextBullet = i;
			break;
		}
	}

	return nextBullet;
}
