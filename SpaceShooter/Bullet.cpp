#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::FloatRect levelBounds)
{
	isActive = false;
	this->levelBounds = levelBounds;
}

bool Bullet::initialize()
{
	isActive = false;

	if (!bulletTexture.loadFromFile("Assets/Graphics/Lasers/laserBlue02.png"))
	{
		return false;
	}

	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(sf::Vector2f(0.75f, 0.75f));

	sf::FloatRect bounds = bulletSprite.getLocalBounds();

	sf::Vector2f origin;
	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.top + (bounds.height / 2);

	bulletSprite.setOrigin(origin);
	bulletSprite.setPosition(inactivePosition);

	return true;
}

void Bullet::update(float deltaTime)
{
	if (isActive)
	{
		float rotation = bulletSprite.getRotation() - 90;

		sf::Vector2f currentPosition = bulletSprite.getPosition();
		currentPosition.x += static_cast<float>(cos(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);
		currentPosition.y += static_cast<float>(sin(rotation * (3.14159265 / 180)) * moveSpeed * deltaTime);

		bulletSprite.setPosition(currentPosition);

		currentPosition = bulletSprite.getPosition();
		bool isOutOfBoundsX = (currentPosition.x < levelBounds.left || currentPosition.x > (levelBounds.left + levelBounds.width));
		bool isOutOfBoundsY = (currentPosition.y < levelBounds.top || currentPosition.y > (levelBounds.top + levelBounds.height));

		if (isOutOfBoundsX || isOutOfBoundsY)
		{
			destroy();
		} 

		if (destroyTimer < destroyDelay)
		{
			destroyTimer += deltaTime;

			if (destroyTimer >= destroyDelay)
			{
				destroy();
			}
		}
	}
}

void Bullet::draw(sf::RenderWindow* window)
{
	if (isActive)
	{
		window->draw(bulletSprite);
	}
}

void Bullet::spawn(sf::Vector2f position, float rotation)
{
	bulletSprite.setRotation(rotation);
	bulletSprite.setPosition(position);

	isActive = true;
}

void Bullet::destroy()
{
	isActive = false;
	bulletSprite.setPosition(inactivePosition);
}
