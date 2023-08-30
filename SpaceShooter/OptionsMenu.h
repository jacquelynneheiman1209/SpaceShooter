#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Switch.h"
#include "GreenButton.h"
#include "RedButton.h"
#include "Slider.h"

#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

class OptionsMenu : public Menu
{
public:
	OptionsMenu();

	bool initialize(sf::FloatRect windowBounds) override;
	void handleInput(sf::RenderWindow* window, sf::Event* event) override;
	void draw(sf::RenderWindow* window) override;

protected:
	Slider sfxVolumeSlider;
	Slider musicVolumeSlider;
	Switch fullscreenSwitch;
	GreenButton saveButton;
	RedButton resetButton;

	bool initializeBackground() override;
	bool initializeText() override;
	bool initializeButtons() override;
};

#endif // !PAUSE_MENU_H



