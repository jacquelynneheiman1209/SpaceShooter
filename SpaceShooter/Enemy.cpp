#include "Enemy.h"
#include "Debug.h"

Enemy::Enemy()
{
    isActive = false;
    isInGameBounds = false;
    isAtInactivePosition = false;

	inactivePosition  = sf::Vector2f(-1000, -1000);
	scale = sf::Vector2f(1, 1);
}

bool Enemy::initialize()
{
	if (textures.size() > 0)
	{
		// select a random texture from the list of textures
		int randomTexture = rand() % textures.size();

		// load the texture
		if (!texture.loadFromFile(textures[randomTexture]))
		{
			return false;
		}

		// setup the sprite
		sprite.setTexture(texture);
		sprite.setScale(scale);
		sprite.setOrigin(getSpriteOrigin());
		sprite.setPosition(inactivePosition);
		sprite.setRotation(static_cast<float>(rand() % 360));
	}

	// randomly select a move speed
	moveSpeed = (rand() % maxMoveSpeed) + minMoveSpeed;

	return true;
}

void Enemy::update(float deltaTime, sf::Vector2f targetPosition)
{
	if (isActive)
	{
		move(deltaTime, targetPosition);
	}
	else
	{
		if (sprite.getPosition() != inactivePosition)
		{
			move(deltaTime, targetPosition);
		}
	}

	if (sprite.getPosition() == inactivePosition)
	{
		isAtInactivePosition = true;
	}
	else
	{
		isAtInactivePosition = false;
	}
}

void Enemy::draw(sf::RenderWindow* window)
{
    if (isActive)
    {
        window->draw(sprite);
    }
}

void Enemy::spawn(sf::Vector2f playerPosition, sf::FloatRect gameBounds)
{
	this->gameBounds = gameBounds;

	ScreenEdge randomScreenEdge = static_cast<ScreenEdge>(rand() % 4);

	sf::Vector2f spawnPosition;

	if (randomScreenEdge == ScreenEdge::LEFT)
	{
		spawnPosition.x = gameBounds.left - 200;
		spawnPosition.y = static_cast<float>((rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100);
	}

	if (randomScreenEdge == ScreenEdge::RIGHT)
	{
		spawnPosition.x = (gameBounds.left + gameBounds.width) + 200;
		spawnPosition.y = static_cast<float>((rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100);
	}

	if (randomScreenEdge == ScreenEdge::TOP)
	{
		spawnPosition.x = static_cast<float>((rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100);
		spawnPosition.y = gameBounds.top - 200;
	}

	if (randomScreenEdge == ScreenEdge::BOTTOM)
	{
		spawnPosition.x = static_cast<float>((rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100);
		spawnPosition.y = (gameBounds.top + gameBounds.height) + 200;
	}

	sprite.setPosition(spawnPosition);
}

void Enemy::destroy()
{
	AudioManager::Play(AudioManager::SoundType::Destroy);
	isActive = false;
	sprite.setPosition(inactivePosition);
}

void Enemy::reposition(sf::FloatRect newGameBounds)
{
	if (isActive || (!isActive && !isAtInactivePosition))
	{
		float percentX = sprite.getPosition().x / (gameBounds.left + gameBounds.width);
		float percentY = sprite.getPosition().y / (gameBounds.top + gameBounds.height);

		float newX = percentX * (newGameBounds.left + newGameBounds.width);
		float newY = percentY * (newGameBounds.top + newGameBounds.height);

		sprite.setPosition(newX, newY);
	}

	gameBounds = newGameBounds;
}

sf::FloatRect Enemy::getCollider()
{
	return sprite.getGlobalBounds();
}

void Enemy::move(float deltaTime, sf::Vector2f playerPosition)
{
	// handled in the child class
}

bool Enemy::isInBounds()
{
	sf::Vector2f position = sprite.getPosition();

	bool isInBoundsX = (position.x > gameBounds.left && position.x < (gameBounds.left + gameBounds.width));
	bool isInBoundsY = (position.y > gameBounds.top && position.y < (gameBounds.top + gameBounds.height));

	return isInBoundsX && isInBoundsY;
}

sf::Vector2f Enemy::getSpriteOrigin()
{
	sf::FloatRect spriteBounds = sprite.getLocalBounds();

	sf::Vector2f origin;
	origin.x = spriteBounds.left + (spriteBounds.width / 2);
	origin.y = spriteBounds.top + (spriteBounds.height / 2);

	return origin;
}

void Enemy::setActive()
{
	if (!isActive)
	{
		if (!isAtInactivePosition && isInGameBounds)
		{
			isActive = true;
		}
	}
}
