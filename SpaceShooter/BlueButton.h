#pragma once
#include "Button.h"

#ifndef BLUE_BUTTON_H
#define BLUE_BUTTON_H

class BlueButton : public Button
{
public:
	BlueButton(sf::Vector2f position, std::string text);

	bool initialize(sf::FloatRect windowSize);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	bool isClicked(sf::Vector2i mousePosition);

	void setScale(float scaleX, float scaleY) override;
	void setScale(sf::Vector2f scale) override;

	void click();

	sf::Vector2f getScale();

private:
	sf::Texture buttonHoverTexture;
};

#endif // !BLUE_BUTTON_H



