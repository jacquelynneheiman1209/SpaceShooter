#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Bullet.h"
#include "AudioManager.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(sf::Vector2f startPosition, sf::FloatRect levelBounds);

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void loseLife();
	void gainLife();
	int getLives();

	sf::FloatRect getCollider();
	std::vector<Bullet*> getBullets();

	sf::Vector2f getPosition();

private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	sf::Vector2f startPosition;
	sf::Vector2f playerScale = sf::Vector2f(0.5f, 0.5f);

	sf::FloatRect levelBounds;

	int lives = 3;
	int totalNumberOfBullets = 20;

	std::vector<std::unique_ptr<Bullet>> bullets;

	float moveSpeed = 300;
	float rotateSpeed = 150;

	float shootTimer = 0;				
	float shootDelaySeconds = 0.5;		// shoot twice per second

	bool moveForwards = false;
	bool moveBackwards = false;
	bool rotateLeft = false;
	bool rotateRight = false;
	bool shootBullet = false;

	bool isDead = false;
	bool canShoot = true;

	void move(float deltaTime);
	void rotate(float deltaTime);
	void shoot();
	void resetPosition();

	int getNextBulletIndex();

};

#endif // !PLAYER_H


