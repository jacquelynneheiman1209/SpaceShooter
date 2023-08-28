#pragma once
#include <SFML/Graphics.hpp>

#ifndef MENU_H
#define MENU_H

class Menu
{
public:
	Menu();

	virtual bool initialize(sf::FloatRect gameBounds);
	virtual void handleInput(sf::RenderWindow* window, sf::Event* event);
	virtual void draw(sf::RenderWindow* window);

protected:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;
	sf::Text titleText;

	sf::FloatRect gameBounds;

	void setupText(sf::Text* text, std::string textString = "", int characterSize = 20, sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::White);

	void setupSprite(sf::Sprite* sprite, sf::Texture* texture, sf::Vector2f scale, sf::Vector2f position);
	
	sf::Vector2f getCenter(sf::FloatRect bounds);

	virtual bool initializeBackground();
	virtual bool initializeText();
	virtual bool initializeButtons();


};

#endif // !MENU_H

