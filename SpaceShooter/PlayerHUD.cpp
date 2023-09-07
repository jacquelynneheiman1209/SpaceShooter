#include "PlayerHUD.h"
#include <iostream>
#include <algorithm>

PlayerHUD::PlayerHUD(sf::FloatRect screenRect) : killPlayerButton(sf::Vector2f(0, 0), "Kill Player")
{
	screenBounds = screenRect;
}

bool PlayerHUD::initialize(sf::FloatRect windowBounds)
{
	screenBounds = windowBounds;

	if (!lifeTexture.loadFromFile("Assets/Graphics/UI/playerLife1_blue.png"))
	{
		std::cout << "PlayerHUD.cpp : Could not load 'lifeTexture' from 'Assets/Graphics/UI/playerLife1_blue.png'" << std::endl;
		return false;
	}

	lifeSprite.setTexture(lifeTexture);
	
	sf::FloatRect bounds = lifeSprite.getLocalBounds();

	sf::Vector2f origin;
	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.top + (bounds.height / 2);

	sf::Vector2f position;
	position.x = windowBounds.left + (50 + (bounds.width / 2));
	position.y = windowBounds.top + (50 + (bounds.height / 2));

	lifeSprite.setOrigin(origin);
	lifeSprite.setPosition(position);

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		std::cout << "PlayerHUD.cpp : Could not load 'font'" << std::endl;
		return false;
	}

	livesText.setFont(font);
	livesText.setString("x 3");
	livesText.setCharacterSize(25);
	
	bounds = livesText.getLocalBounds();

	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.top + (bounds.height / 2);

	position.x = (lifeSprite.getPosition().x + (lifeSprite.getLocalBounds().width / 2)) + (bounds.width / 2) + 10;
	position.y = lifeSprite.getPosition().y;

	livesText.setOrigin(origin);
	livesText.setPosition(position);

	scoreText.setFont(font);
	scoreText.setString("000000");
	scoreText.setCharacterSize(25);

	bounds = scoreText.getLocalBounds();

	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.left + (bounds.height / 2);

	position.x = (screenBounds.left + screenBounds.width) - (bounds.width / 2) - 50;
	position.y = livesText.getPosition().y;

	scoreText.setOrigin(origin);
	scoreText.setPosition(position);

	return true;
}

void PlayerHUD::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	killPlayerButton.handleInput(window, event);
}

void PlayerHUD::update(float deltaTime, int playerLives, int score)
{
	livesText.setString("x " + std::to_string(playerLives));
	scoreText.setString(getScoreString(score));
}

void PlayerHUD::draw(sf::RenderWindow* window)
{
	window->draw(lifeSprite);
	window->draw(livesText);
	window->draw(scoreText);
}

std::string PlayerHUD::getScoreString(int score)
{
	std::string scoreAsString = std::to_string(score);
	size_t scoreLength = 6;

	int numZerosToAdd = static_cast<int>(scoreLength - std::min(scoreLength, scoreAsString.size()));
	
	return std::string(numZerosToAdd, '0').append(scoreAsString);
}
