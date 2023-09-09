#pragma once
#include <SFML/Graphics.hpp>

#ifndef TEXTBOX_H
#define TEXTBOX_H

class Textbox
{
public:
	Textbox(std::string value, int characterSize, sf::Vector2f position);

	bool initialize();
	void setText(std::string text);
	void setPosition(sf::Vector2f position);

	void draw(sf::RenderWindow* window);

private:
	sf::Font font;
	sf::Text text;

	std::string value;
	int characterSize;
	sf::Vector2f position;

	void setOrigin();
};

#endif // !TEXTBOX_H



