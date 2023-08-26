#include "EnemyShip.h"
#include "Debug.h"


EnemyShip::EnemyShip()
{
	isActive = false;
	isAtInactivePosition = false;
	isInGameBounds = false;
}

bool EnemyShip::initialize()
{
	Debug::Log("-------------------------");
	Debug::Log("Initializing EnemyShip...");

	int randomEnemy = rand() % static_cast<int>(textures.size());
	
	if (!enemyTexture.loadFromFile(textures[randomEnemy]))
	{
		Debug::Log("EnemyShip.cpp : Could not load 'enemyTexture' from " + textures[randomEnemy]);
		return false;
	}

	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(enemyScale);

	sf::FloatRect bounds = enemySprite.getLocalBounds();

	sf::Vector2f origin;
	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.top + (bounds.height / 2);

	enemySprite.setOrigin(origin);
	enemySprite.setPosition(inactivePosition);

	Debug::Log("Enemy Starting Position: " + inactivePosition.toString());

	return true;
}

void EnemyShip::update(float deltaTime, sf::Vector2f targetPosition)
{
	if (isActive)
	{
		move(deltaTime, targetPosition);
	}
	else
	{
		if (enemySprite.getPosition() != inactivePosition)
		{
			move(deltaTime, targetPosition);
		}
	}

	if (enemySprite.getPosition() == inactivePosition)
	{
		isAtInactivePosition = true;
	}
	else
	{
		isAtInactivePosition = false;
	}
}

void EnemyShip::draw(sf::RenderWindow* window)
{
	if (isActive)
	{
		window->draw(enemySprite);
	}
}

void EnemyShip::spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds)
{
	Debug::Log("Spawning Enemy Ship...");

	this->gameBounds = gameBounds;

	ScreenEdge randomScreenEdge = static_cast<ScreenEdge>(rand() % 4);

	sf::Vector2f spawnPosition;

	if (randomScreenEdge == ScreenEdge::LEFT)
	{
		Debug::Log("Screen Edge: LEFT");
		spawnPosition.x = gameBounds.left - 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::RIGHT)
	{
		Debug::Log("Screen Edge: RIGHT");
		spawnPosition.x = (gameBounds.left + gameBounds.width) + 200;
		spawnPosition.y = (rand() % static_cast<int>((gameBounds.top + gameBounds.height) - 200)) + 100;
	}

	if (randomScreenEdge == ScreenEdge::TOP)
	{
		Debug::Log("Screen Edge: TOP");
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = gameBounds.top - 200;
	}

	if (randomScreenEdge == ScreenEdge::BOTTOM)
	{
		Debug::Log("Screen Edge: BOTTOM");
		spawnPosition.x = (rand() % static_cast<int>((gameBounds.left + gameBounds.width))) + 100;
		spawnPosition.y = (gameBounds.top + gameBounds.height) + 200;
	}

	enemySprite.setPosition(spawnPosition);

	Debug::Log("Player Position: " + targetPosition.toString());
	Debug::Log("Enemy Spawn Position: " + spawnPosition.toString());
}

void EnemyShip::destroy()
{
	isActive = false;
	enemySprite.setPosition(inactivePosition);
}

sf::FloatRect EnemyShip::getCollider()
{
	return enemySprite.getGlobalBounds();
}

void EnemyShip::move(float deltaTime, sf::Vector2f targetPosition)
{
	float dx = enemySprite.getPosition().x - targetPosition.x;
	float dy = enemySprite.getPosition().y - targetPosition.y;

	float rotation = ((atan2(dy, dx)) * 180 / 3.14159265) + 90;

	sf::Vector2f currentPosition = enemySprite.getPosition();
	currentPosition.x += static_cast<float>(cos((rotation + 90) * (3.14159265 / 180)) * moveSpeed * deltaTime);
	currentPosition.y += static_cast<float>(sin((rotation + 90) * (3.14159265 / 180)) * moveSpeed * deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		Debug::Log("Enemy Ship Position: " + currentPosition.toString());
	}

	bool isInBoundsX = (currentPosition.x > gameBounds.left && currentPosition.x < (gameBounds.left + gameBounds.width));
	bool isInBoundsY = (currentPosition.y > gameBounds.top && currentPosition.y < (gameBounds.top + gameBounds.height));

	isInGameBounds = isInBoundsX && isInBoundsY;

	enemySprite.setRotation(rotation);
	enemySprite.setPosition(currentPosition);

	if (!isActive)
	{
		if (!isAtInactivePosition && isInGameBounds)
		{
			isActive = true;
		}
	}
}
