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
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:

	// DEVELOPMENT-TESTING BUTTONS
	RedButton killPlayerButton;
	YellowButton killEnemyButton;
};

#endif // !PLAYER_HUD

