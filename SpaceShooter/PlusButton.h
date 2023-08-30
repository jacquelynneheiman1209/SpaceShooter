#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

#ifndef PLUS_BUTTON_H
#define PLUS_BUTTON_H

class PlusButton : public Button
{
public:
	PlusButton(sf::Vector2f position, std::string buttonText);

	bool initialize(sf::FloatRect windowSize);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	bool isMouseOver(sf::Vector2i mousePosition);

	void click();

	sf::Vector2f getSize();
	sf::Vector2f getPosition();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

	sf::FloatRect getBounds(); 

private:
	sf::Texture buttonHoverTexture;

	sf::Vector2f getCenter(sf::FloatRect bounds);
};

#endif // !PLUS_BUTTON_H



