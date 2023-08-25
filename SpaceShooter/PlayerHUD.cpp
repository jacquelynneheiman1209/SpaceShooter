#include "PlayerHUD.h"
#include <iostream>

PlayerHUD::PlayerHUD() : killPlayerButton(sf::Vector2f(0, 0), "Kill Player"), killEnemyButton(sf::Vector2f(0, 0), "Kill Enemy")
{

}

bool PlayerHUD::initialize()
{
	if (!font.loadFromFile("Assets/Fonts/kenvector_future.ttf"))
	{
		std::cout << "PlayerHUD.cpp : Could not load 'font'" << std::endl;
		return false;
	}

	sf::FloatRect textBounds;
	sf::Vector2f textPosition;

	livesText.setFont(font);
	livesText.setString("Lives: ");
	livesText.setCharacterSize(25);
	
	textBounds = livesText.getLocalBounds();
	textPosition.x = 50 + (textBounds.width / 2);
	textPosition.y = 20 + (textBounds.height / 2);;

	livesText.setOrigin(textBounds.left + (textBounds.width / 2), textBounds.top + (textBounds.height / 2));
	livesText.setPosition(textPosition);

	enemiesRemainingText.setFont(font);
	enemiesRemainingText.setString("Enemies Remaining: ");
	enemiesRemainingText.setCharacterSize(25);

	textBounds = enemiesRemainingText.getLocalBounds();
	textPosition.x = (livesText.getPosition().x + (livesText.getLocalBounds().width / 2)) + (textBounds.width / 2) + 100;
	textPosition.y = 20 + (textBounds.height / 2);

	enemiesRemainingText.setOrigin(textBounds.left + (textBounds.width / 2), textBounds.top + (textBounds.height / 2));
	enemiesRemainingText.setPosition(textPosition);

	killPlayerButton = RedButton(sf::Vector2f(158, 667), "Lose Life");
	killEnemyButton = RedButton(sf::Vector2f(450, 667), "Defeat Enenemy");

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

void PlayerHUD::update(float deltaTime, int playerLives, int enemiesRemaining)
{
	livesText.setString("Lives: " + std::to_string(playerLives));
	enemiesRemainingText.setString("Enemies Remaining: " + std::to_string(enemiesRemaining));
}

void PlayerHUD::draw(sf::RenderWindow* window)
{
	window->draw(livesText);
	window->draw(enemiesRemainingText);
	killPlayerButton.draw(window);
	killEnemyButton.draw(window);
}
