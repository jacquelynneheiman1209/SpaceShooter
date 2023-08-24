#pragma once
#include <SFML/Graphics.hpp>
#include "RedButton.h"
#include "YellowButton.h"

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

	YellowButton continueGameButton;
	YellowButton restartLevelButton;
	YellowButton optionsButton;
	RedButton quitButton;

private:
	sf::Texture menuBackgroundTexture;
	sf::Texture buttonTexture;

	sf::Sprite menuBackgroundSprite;

	sf::Font font;

	sf::Text menuTitleText;

	void setupSprite(sf::Sprite* sprite, sf::Vector2f position);
	void setupText(sf::Text* text, sf::Vector2f position, std::string textString);
};

#endif // !PAUSE_MENU_H


