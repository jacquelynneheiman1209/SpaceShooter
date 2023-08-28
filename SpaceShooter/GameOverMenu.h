#pragma once
#include <SFML/Graphics.hpp>
#include "GreenButton.h"
#include "RedButton.h"
#include "Menu.h"

#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

class GameOverMenu : public Menu
{
public:
	GameOverMenu();

	bool initialize(sf::FloatRect windowBounds) override;
	void handleInput(sf::RenderWindow* window, sf::Event* event) override;
	void draw(sf::RenderWindow* window) override;

	GreenButton playAgainButton;
	RedButton mainMenuButton;

protected:
	sf::Text playAgainText;

	bool initializeBackground() override;
	bool initializeText() override;
	bool initializeButtons() override;
};

#endif // !GAME_OVER_MENU_H



