#include "GameHUD.h"
#include <iostream>

GameHUD::GameHUD()
{

}

bool GameHUD::initialize(int initialLives)
{
	// TODO: This function is not getting called, but I am calling it
	std::cout << "Initialize GameHUD" << std::endl;

	if (!livesTexture.loadFromFile("Assets/Graphics/UI/playerLife1_blue.png"))
	{
		std::cout << "GameHUD.cpp : Could not load 'livesTexture'" << std::endl;
		return false;
	}

	// TODO: Initialize Sprites 

	return true;
}

void GameHUD::draw(sf::RenderWindow* window, int playerLives)
{
	// TODO: Draw Sprites
}
