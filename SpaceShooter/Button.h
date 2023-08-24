#pragma once
#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
	Button(sf::Vector2f position, std::string text);
	Button(sf::Vector2f position, std::string text, sf::Color color, sf::Color hoverColor);

	virtual bool initialize();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	void handleInput(sf::RenderWindow* window, sf::Event* event);

	bool isClicked(sf::Vector2i mousePosition);

	virtual void setScale(float scaleX, float scaleY);
	virtual void setScale(sf::Vector2f scale);

protected:
	sf::Texture buttonTexture;		// for children that want to use sprites
	sf::Sprite buttonSprite;		// for children that want to use sprites

	sf::RectangleShape buttonBackground;	// default button background

	sf::Font font;
	sf::Text text;

	sf::Vector2f buttonPosition;
	std::string buttonText;

	sf::Color buttonColor = sf::Color::White;
	sf::Color buttonHoverColor = sf::Color::Transparent;
};

#endif // !BUTTON_H


