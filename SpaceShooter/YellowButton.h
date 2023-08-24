#pragma once
#include "Button.h"

#ifndef PAUSE_MENU_BUTTON_H
#define PAUSE_MENU_BUTTON_H

class YellowButton : public Button
{
public:
	YellowButton(sf::Vector2f position, std::string text);

	bool initialize() override;

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	bool isClicked(sf::Vector2i mousePosition);

	void setScale(float scaleX, float scaleY) override;
	void setScale(sf::Vector2f scale) override;

	sf::Vector2f getScale();

private:
	sf::Texture buttonHoverTexture;
};

#endif // !PAUSE_MENU_BUTTON_H



