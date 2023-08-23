#pragma once
#include <SFML/Graphics.hpp>

#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

class OptionsMenu
{
public:
	OptionsMenu();

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	sf::Texture menuBackgroundTexture;
	sf::Sprite menuBackgroundSprite;

	sf::Font font;

	sf::Text menuTitleText;

	void setupSprite(sf::Sprite* sprite, sf::Vector2f position);
	void setupText(sf::Text* text, sf::Vector2f position, std::string textString);
};

#endif // !PAUSE_MENU_H



