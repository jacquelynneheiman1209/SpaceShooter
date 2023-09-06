#pragma once
#include <SFML/Graphics.hpp>
#include "MinusButton.h"
#include "PlusButton.h"

#ifndef SLIDER_H
#define SLIDER_H

class Slider
{
public:
	Slider(sf::FloatRect parentBounds, sf::Vector2f position, std::string labelText);

	bool initialize(sf::FloatRect parentBounds);
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();

	void setPosition(float x, float y);
	int getValue();

private:
	PlusButton plusButton;
	MinusButton minusButton;

	sf::Texture backgroundTexture;
	sf::Texture fillTexture;

	sf::Sprite backgroundSprite;
	std::vector<std::unique_ptr<sf::Sprite>> fillSprites;
	std::vector<bool> showFillSprites;

	sf::Vector2f position;

	sf::Font font;
	sf::Text label;

	std::string labelText;

	void setupSprite(sf::Sprite* sprite, sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale = sf::Vector2f(0, 0));
	
	void increaseValue();
	void decreaseValue();

	sf::Vector2f getCenter(sf::FloatRect bounds);

	float buttonSpacing = 10;

	int minValue = 0;
	int maxValue = 10;

	int value = 10;

	sf::FloatRect parentBounds;
	
};

#endif // !SLIDER_H



