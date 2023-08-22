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
	sf::Texture menuTexture;
	sf::Texture buttonTexture;
};

#endif // !PAUSE_MENU_H



