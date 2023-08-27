#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "GreenButton.h"
#include "RedButton.h"
#include "SceneLoader.h"
#include "BlueButton.h"


#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

class MainMenuScene : public Scene
{
public:
	MainMenuScene(SceneLoader* sceneLoader, sf::FloatRect windowSize);

	bool initialize(sf::FloatRect windowBounds);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void draw(sf::RenderWindow* window) override;

	void handleWindowResize(sf::FloatRect newWindowSize);

private:
	sf::Font font;
	sf::Text gameTitleText;

	sf::FloatRect windowSize;

	SceneLoader* sceneLoader;

	GreenButton startGameButton;
	BlueButton optionsButton;
	RedButton quitGameButton;

	void setupText(sf::Text* text, sf::Vector2f position, std::string textValue, int characterSize, sf::Color textFillColor, sf::Color textOutlineColor);
};

#endif // !MAIN_MENU_SCENE_H



