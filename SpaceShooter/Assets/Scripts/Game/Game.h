#pragma once
#include <SFML/Graphics.hpp>
#include "../Background/Background.h"
#include "../SceneManager/SceneManager.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game();

	bool initialize();
	void run();

private:
	int windowWidth = (sf::VideoMode::getDesktopMode().width / 3) * 2;
	int windowHeight = (sf::VideoMode::getDesktopMode().height / 3) * 2;

	sf::Clock gameClock;
	float deltaTime = 0;

	Background background;
	SceneManager sceneManager;

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);

	bool loadBackground();
};

#endif // !GAME_H


