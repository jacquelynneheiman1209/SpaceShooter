#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "GreenButton.h"
#include "RedButton.h"
#include "SceneLoader.h"


#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

class MainMenuScene : public Scene
{
public:
	MainMenuScene(SceneLoader* sceneLoader);

	bool initialize() override;

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;

private:
	sf::Font font;
	sf::Text gameTitleText;

	SceneLoader* sceneLoader;

	GreenButton startGameButton;
	RedButton quitGameButton;

	void setupText(sf::Text* text, sf::Vector2f position, std::string textValue, int characterSize, sf::Color textFillColor, sf::Color textOutlineColor);
};

#endif // !MAIN_MENU_SCENE_H



