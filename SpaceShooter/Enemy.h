#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef ENEMY_H

class Enemy
{
public:
	bool isActive = false;
	bool isAtInactivePosition = false;
	bool isInGameBounds = false;

	enum ScreenEdge { LEFT, TOP, RIGHT, BOTTOM };

	Enemy();

	virtual bool initialize();
	virtual void update(float deltaTime, sf::Vector2f targetPosition = sf::Vector2f(0, 0));
	void draw(sf::RenderWindow* window);

	virtual void spawn(sf::Vector2f playerPosition, sf::FloatRect gameBounds);
	void destroy();

	void reposition(sf::FloatRect newGameBounds);

	sf::FloatRect getCollider();

protected:
	std::vector<std::string> textures;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f scale;

	sf::SoundBuffer destroySoundBuffer;
	sf::Sound destroySound;

	sf::FloatRect gameBounds;

	sf::Vector2f inactivePosition;
	sf::Vector2f playerPosition;

	int minMoveSpeed = 0;
	int maxMoveSpeed = 0;
	int moveSpeed = 0;

	virtual void move(float deltaTime, sf::Vector2f playerPosition);

	bool isInBounds();
	sf::Vector2f getSpriteOrigin();

	void setActive();
};

#endif // !ENEMY_H




