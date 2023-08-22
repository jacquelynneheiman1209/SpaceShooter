#pragma once
#include <SFML/Graphics.hpp>

#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

class PauseMenu
{
public:
	PauseMenu();

	bool initialize();
	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

private:
	sf::Texture menuBackgroundTexture;
	sf::Texture buttonTexture;

	sf::Sprite menuBackgroundSprite;

	sf::Vector2f menuBackgroundScale = sf::Vector2f(3, 3);

	sf::Font font;

	sf::Text menuTitleText;

	void setupSprite(sf::Sprite* sprite, sf::Vector2f position);
	void setupText(sf::Text* text, sf::Vector2f position, std::string textString);
};

#endif // !PAUSE_MENU_H



