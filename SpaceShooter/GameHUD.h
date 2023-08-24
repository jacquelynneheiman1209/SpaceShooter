#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef GAME_HUD_H
#define GAME_HUD_H

class GameHUD
{
public:
	GameHUD();

	bool initialize(int initialLives);

	void draw(sf::RenderWindow* window, int playerLives);

private:
	sf::Texture livesTexture;
	std::vector<sf::Sprite> livesSprites;

	float startX = 10;
	float startY = 10;

};

#endif // !GAME_HUD_H



