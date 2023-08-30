#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

#ifndef MINUS_BUTTON_H
#define MINUS_BUTTON_H

class MinusButton : public Button
{
public:
	MinusButton(sf::Vector2f position, std::string buttonText);

	bool initialize(sf::FloatRect windowSize);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	bool isMouseOver(sf::Vector2i mousePosition);

	void click();

	sf::Vector2f getSize();
	sf::FloatRect getBounds();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

private:
	sf::Texture buttonHoverTexture;

	sf::Vector2f getCenter(sf::FloatRect bounds);
};

#endif // !PLUS_BUTTON_H



