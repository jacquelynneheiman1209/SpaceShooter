#pragma once
#include "../../../../../UI Elements/Button/Button.h"

#ifndef PAUSE_MENU_QUIT_BUTTON_H
#define PAUSE_MENU_QUIT_BUTTON_H

class PauseMenuQuitButton : public Button
{
public:
	PauseMenuQuitButton(sf::Vector2f position, std::string text);

	bool initialize() override;
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	bool isClicked(sf::Vector2i mousePosition);

private:
	sf::Texture buttonHoverTexture;

};

#endif // !PAUSE_MENU_QUIT_BUTTON_H



