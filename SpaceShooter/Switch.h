#pragma once
#include <SFML/Graphics.hpp>

#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
public:
	Switch(sf::Vector2f position, std::string textString, sf::FloatRect parentBounds);

	bool initialize(sf::FloatRect parentBounds);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window);

	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();

	sf::Vector2f getOrigin();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

	bool getValue();

protected:
	sf::FloatRect parentBounds;

	sf::Texture onTexture;
	sf::Texture offTexture;

	sf::Sprite switchSprite;

	sf::Font font;
	sf::Text text;

	sf::Vector2f position;

	std::string textString;

	float regularRotation;
	float hoverRotation;

	float textSpacing = 20;

	bool value = false;

	bool isMouseOver(sf::Vector2i mousePosition);
};


#endif // !SWITCH_H

