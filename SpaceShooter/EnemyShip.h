#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H

class EnemyShip
{
public:
	enum ScreenEdge { LEFT, TOP, RIGHT, BOTTOM};
	EnemyShip();

	bool initialize();
	void update(float deltaTime, sf::Vector2f targetPosition);
	void draw(sf::RenderWindow* window);

	void spawn(sf::Vector2f targetPosition, sf::FloatRect gameBounds);
	void destroy();

	void reposition(sf::FloatRect newGameBounds);

	sf::FloatRect getCollider();

	bool isActive;
	bool isInGameBounds;
	bool isAtInactivePosition;

private:
	std::vector<std::string> textures {
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

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;

	sf::Vector2f enemyScale = sf::Vector2f(0.5f, 0.5f);
	sf::Vector2f inactivePosition = sf::Vector2f(-1000, -1000);

	sf::SoundBuffer destroySoundBuffer;
	sf::Sound destroySound;

	sf::FloatRect gameBounds;

	float moveSpeed = 150;

	void move(float deltaTime, sf::Vector2f targetPosition);

};

#endif // !ENEMY_SHIP_H




