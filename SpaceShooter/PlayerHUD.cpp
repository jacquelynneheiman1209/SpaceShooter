#include "PlayerHUD.h"
#include <iostream>

PlayerHUD::PlayerHUD() : killPlayerButton(sf::Vector2f(0, 0), "Kill Player"), killEnemyButton(sf::Vector2f(0, 0), "Kill Enemy")
{
	std::cout << "Creating PlayerHUD..." << std::endl;
}

bool PlayerHUD::initialize()
{
	std::cout << "Initializing PlayerHUD..." << std::endl;

	killPlayerButton = RedButton(sf::Vector2f(158, 667), "Lose Life");
	killEnemyButton = YellowButton(sf::Vector2f(450, 667), "Defeat Enenemy");

	if (!killPlayerButton.initialize())
	{
		std::cout << "PlayerHUD.cpp : Could not load 'killPlayerButton'" << std::endl;
		return false;
	}

	if (!killEnemyButton.initialize())
	{
		std::cout << "PlayerHUD.cpp : Could not load 'killEnemyButton'" << std::endl;
		return false;
	}

	return true;
}

void PlayerHUD::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	killPlayerButton.handleInput(window, event);
	killEnemyButton.handleInput(window, event);
}

void PlayerHUD::update(float deltaTime)
{

}

void PlayerHUD::draw(sf::RenderWindow* window)
{
	killPlayerButton.draw(window);
	killEnemyButton.draw(window);
}
