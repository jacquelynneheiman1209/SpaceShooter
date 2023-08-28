#include "GameOverMenu.h"
#include <iostream>

GameOverMenu::GameOverMenu() : Menu(), playAgainButton(sf::Vector2f(0, 0), "Play Again"), mainMenuButton(sf::Vector2f(0, 0), "Main Menu")
{

}

bool GameOverMenu::initialize(sf::FloatRect windowBounds)
{
	// initializes the font and saves windowBounds
	if (!Menu::initialize(windowBounds))
	{
		return false;
	}

	// setup the menu background
	if (!initializeBackground())
	{
		return false;
	}

	// setup the text on the menu
	if (!initializeText())
	{
		return false;
	}

	// setup the buttons on the menu
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

void GameOverMenu::draw(sf::RenderWindow* window)
{
	// draw the background sprite & title text
	Menu::draw(window);

	// draw text
	window->draw(playAgainText);

	// draw buttons
	playAgainButton.draw(window);
	mainMenuButton.draw(window);
}

bool GameOverMenu::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/GameOverMenu_Background.png"))
	{
		return false;
	}

	setupSprite(&backgroundSprite, &backgroundTexture, sf::Vector2f(1, 1), getCenter(gameBounds));

	return true;
}

bool GameOverMenu::initializeText()
{
	sf::Vector2f textPosition = getCenter(backgroundSprite.getGlobalBounds());
	textPosition.y = backgroundSprite.getGlobalBounds().top + 27;

	setupText(&titleText, "Game Over", 40, textPosition);

	textPosition.y = backgroundSprite.getGlobalBounds().top + 80;

	setupText(&playAgainText, "Would you like to play again?", 20, textPosition, sf::Color::Black);

	return true;
}

bool GameOverMenu::initializeButtons()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	sf::Vector2f buttonPosition;
	buttonPosition.x = (backgroundBounds.width / 4);
	buttonPosition.y = 150;

	playAgainButton = GreenButton(buttonPosition, "Play Again");

	if (!playAgainButton.initialize(backgroundBounds))
	{
		return false;
	}

	playAgainButton.setScale(.99f, playAgainButton.getScale().y);

	buttonPosition.x = ((backgroundBounds.width / 4) * 3);;
	buttonPosition.y = 150;

	mainMenuButton = RedButton(buttonPosition, "Main Menu");

	if (!mainMenuButton.initialize(backgroundBounds))
	{
		return false;
	}

	mainMenuButton.setScale(.99f, mainMenuButton.getScale().y);

	return true;
}
