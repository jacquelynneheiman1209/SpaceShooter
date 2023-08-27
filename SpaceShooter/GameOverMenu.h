#pragma once
#include <SFML/Graphics.hpp>
#include "GreenButton.h"
#include "RedButton.h"

#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

class GameOverMenu
{
public:
	GameOverMenu();

	bool initialize(sf::FloatRect windowBounds);
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window, bool playerWon);

	GreenButton playAgainButton;
	RedButton mainMenuButton;

private:
	sf::Texture backgroundTexture;	// for use later when I have the art pieces
	sf::Sprite backgroundSprite;	// for use later when I have the art pieces

	sf::RectangleShape backgroundShape;

	sf::Font font;

	sf::Text gameOverText;
	sf::Text playAgainText;

	bool initializeBackground(sf::FloatRect windowBounds);

	bool initializeText();
	bool initializeGameOverText(std::string textString);
	bool initializePlayAgainText();

	bool initializeButtons();
	bool intializePlayAgainButton();
	bool initializeMainMenuButton();
};

#endif // !GAME_OVER_MENU_H



