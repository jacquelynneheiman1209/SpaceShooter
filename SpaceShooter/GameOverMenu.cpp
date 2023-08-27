#include "GameOverMenu.h"
#include <iostream>

GameOverMenu::GameOverMenu() : playAgainButton(sf::Vector2f(0, 0), "Play Again"), mainMenuButton(sf::Vector2f(0, 0), "Main Menu")
{

}

bool GameOverMenu::initialize(sf::FloatRect windowBounds)
{

	if (!initializeBackground(windowBounds))
	{
		return false;
	}

	if (!initializeText())
	{
		return false;
	}

	if (!initializeButtons())
	{
		return false;
	}
	
	return true;
}

void GameOverMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	playAgainButton.handleInput(window, event);
	mainMenuButton.handleInput(window, event);
}

void GameOverMenu::update(float deltaTime)
{
}

void GameOverMenu::draw(sf::RenderWindow* window, bool playerWon)
{
	if (playerWon)
	{
		initializeGameOverText("You Win!");
	}
	else
	{
		initializeGameOverText("Game Over!");
	}

	window->draw(backgroundSprite);
	window->draw(gameOverText);
	window->draw(playAgainText);
	playAgainButton.draw(window);
	mainMenuButton.draw(window);
}

bool GameOverMenu::initializeBackground(sf::FloatRect windowBounds)
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/GameOverMenu_Background.png"))
	{
		std::cout << "GameOverMenu.cpp : Could not load texture for 'backgroundTexture'" << std::endl;
		return false;
	}

	backgroundSprite.setTexture(backgroundTexture);

	sf::FloatRect backgroundBounds = backgroundSprite.getLocalBounds();

	backgroundSprite.setOrigin(backgroundBounds.left + (backgroundBounds.width / 2), backgroundBounds.top + (backgroundBounds.height / 2));
	backgroundSprite.setPosition(windowBounds.left + (windowBounds.width / 2), windowBounds.top + (windowBounds.height / 2));

	return true;
}

bool GameOverMenu::initializeText()
{
	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		std::cout << "GameOverMenu.cpp : Could not load font for 'font'" << std::endl;
		return false;
	}

	if (!initializeGameOverText("Game Over!"))
	{
		std::cout << "GameOverMenu.cpp : Could not initialize 'gameOverText'" << std::endl;
		return false;
	}

	if (!initializePlayAgainText())
	{
		std::cout << "GameOverMenu.cpp : Could not initialize 'playAgainText'" << std::endl;
		return false;
	}

	return true;
}

bool GameOverMenu::initializeGameOverText(std::string textString)
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();
	sf::FloatRect textBounds;

	gameOverText.setFont(font);
	gameOverText.setString(textString);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::White);

	textBounds = gameOverText.getLocalBounds();

	gameOverText.setOrigin(textBounds.left + (textBounds.width / 2), textBounds.top + (textBounds.height / 2));
	gameOverText.setPosition(backgroundBounds.left + (backgroundBounds.width / 2), backgroundBounds.top + 27);

	return true;
}

bool GameOverMenu::initializePlayAgainText()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();
	sf::FloatRect textBounds;

	playAgainText.setFont(font);
	playAgainText.setString("Would you like to play again?");
	playAgainText.setCharacterSize(20);
	playAgainText.setFillColor(sf::Color::Black);

	textBounds = playAgainText.getLocalBounds();

	playAgainText.setOrigin(textBounds.left + (textBounds.width / 2), textBounds.top + (textBounds.height / 2));
	playAgainText.setPosition(gameOverText.getPosition().x, backgroundBounds.top + 80);

	return true;
}

bool GameOverMenu::initializeButtons()
{
	if (!intializePlayAgainButton())
	{
		return false;
	}

	if (!initializeMainMenuButton())
	{
		return false;
	}

	return true;
}

bool GameOverMenu::intializePlayAgainButton()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	sf::Vector2f buttonPosition;
	buttonPosition.x = backgroundBounds.left + (backgroundBounds.width / 4);
	buttonPosition.y = backgroundBounds.top + 150;

	playAgainButton = GreenButton(buttonPosition, "Play Again");

	if (!playAgainButton.initialize(backgroundBounds))
	{
		return false;
	}

	playAgainButton.setScale(.99f, playAgainButton.getScale().y);

	return true;
}

bool GameOverMenu::initializeMainMenuButton()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	sf::Vector2f buttonPosition;
	buttonPosition.x = backgroundBounds.left + ((backgroundBounds.width / 4) * 3);;
	buttonPosition.y = backgroundBounds.top + 150;

	mainMenuButton = RedButton(buttonPosition, "Main Menu");

	if (!mainMenuButton.initialize(backgroundBounds))
	{
		std::cout << "GameOverMenu.cpp : Could not initialize 'mainMenuButton'" << std::endl;
		return false;
	}

	mainMenuButton.setScale(0.99f, mainMenuButton.getScale().y);

	return false;
}
