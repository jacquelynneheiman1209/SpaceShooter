#pragma once
#include <SFML/Graphics.hpp>
#include "GreenButton.h"
#include "RedButton.h"

#ifndef CONFIRMATION_MENU_H
#define CONFIRMATION_MENU_H

class ConfirmationMenu
{
public:
	ConfirmationMenu();

	bool initialize(sf::FloatRect windowBounds);
	void draw(sf::RenderWindow* window);
	void handleInput(sf::RenderWindow* window, sf::Event* event);

	GreenButton yesButton;
	RedButton noButton;

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;
	sf::Text titleText;
	sf::Text warningText;

	sf::Vector2f getCenter(sf::FloatRect bounds);
	void setText(sf::Text* text, std::string textString, int characterSize, sf::Vector2f textPosition);
};

#endif // !CONFIRMATION_MENU_H



