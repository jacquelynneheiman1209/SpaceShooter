#pragma once
#include <SFML/Graphics.hpp>
#include "RedButton.h"
#include "YellowButton.h"

#ifndef PLAYER_HUD
#define PLAYER_HUD

class PlayerHUD
{
public:
	PlayerHUD();

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime, int playerLives, int enemiesRemaining);
	void draw(sf::RenderWindow* window);

	// DEVELOPMENT-TESTING BUTTONS
	RedButton killPlayerButton;
	RedButton killEnemyButton;

private:

	sf::Font font;

	sf::Text livesText;
	sf::Text enemiesRemainingText;
	
};

#endif // !PLAYER_HUD

