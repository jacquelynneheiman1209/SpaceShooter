#pragma once
#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
	Button(sf::Vector2f position, std::string text);

	bool initialize();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	bool isClicked(sf::Vector2i mousePosition);

private:
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	sf::Font font;
	sf::Text text;

	sf::Vector2f buttonPosition;
	std::string buttonText;
};

#endif // !BUTTON_H


