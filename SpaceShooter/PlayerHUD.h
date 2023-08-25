#pragma once
#include <SFML/Graphics.hpp>
#include "RedButton.h"
#include "YellowButton.h"

#ifndef PLAYER_HUD
#define PLAYER_HUD

class PlayerHUD
{
public:
	PlayerHUD(sf::FloatRect screenRect);

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime, int playerLives, int enemiesRemaining);
	void draw(sf::RenderWindow* window);

	// DEVELOPMENT-TESTING BUTTONS
	RedButton killPlayerButton;

private:
	sf::Texture lifeTexture;
	sf::Sprite lifeSprite;

	sf::Font font;

	sf::Text livesText;
	sf::Text scoreText;

	sf::FloatRect screenBounds;

	std::string getScoreString(int score);
	
};

#endif // !PLAYER_HUD

