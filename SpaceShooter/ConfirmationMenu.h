#pragma once
#include <SFML/Graphics.hpp>
#include "GreenButton.h"
#include "RedButton.h"
#include "Menu.h"

#ifndef CONFIRMATION_MENU_H
#define CONFIRMATION_MENU_H

class ConfirmationMenu : public Menu
{
public:
	ConfirmationMenu();

	bool initialize(sf::FloatRect windowBounds) override;
	void draw(sf::RenderWindow* window) override;
	void handleInput(sf::RenderWindow* window, sf::Event* event) override;

	GreenButton yesButton;
	RedButton noButton;

protected:
	sf::Text warningText;

	bool initializeBackground() override;
	bool initializeText() override;
	bool initializeButtons() override;
};

#endif // !CONFIRMATION_MENU_H



