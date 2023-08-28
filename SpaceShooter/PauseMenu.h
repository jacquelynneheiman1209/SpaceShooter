#pragma once
#include <SFML/Graphics.hpp>
#include "RedButton.h"
#include "BlueButton.h"
#include "Menu.h"

#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

class PauseMenu : public Menu
{
public:
	PauseMenu();

	bool initialize(sf::FloatRect windowBounds) override;
	void handleInput(sf::RenderWindow* window, sf::Event* event) override;
	void draw(sf::RenderWindow* window) override;

	BlueButton continueGameButton;
	BlueButton restartLevelButton;
	BlueButton optionsButton;
	RedButton menuButton;

protected:
	bool initializeBackground() override;
	bool initializeText() override;
	bool initializeButtons() override;

};

#endif // !PAUSE_MENU_H



