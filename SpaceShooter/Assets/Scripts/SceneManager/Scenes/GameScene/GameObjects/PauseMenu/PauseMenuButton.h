#pragma once
#include "../../../../../UI Elements/Button/Button.h"

#ifndef PAUSE_MENU_BUTTON_H
#define PAUSE_MENU_BUTTON_H

class PauseMenuButton : public Button
{
public:
	PauseMenuButton(sf::Vector2f position, std::string text);

	bool initialize() override;

	void handleInput(sf::RenderWindow* window, sf::Event* event);

private:
	sf::Texture buttonHoverTexture;
};

#endif // !PAUSE_MENU_BUTTON_H



