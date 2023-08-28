#include "PauseMenu.h"
#include "Debug.h"

PauseMenu::PauseMenu() : Menu(), continueGameButton(sf::Vector2f(0, 0), "Continue"), restartLevelButton(sf::Vector2f(0, 0), "Resume"), optionsButton(sf::Vector2f(0, 0), "Options"), menuButton(sf::Vector2f(0, 0), "Main Menu")
{

}

bool PauseMenu::initialize(sf::FloatRect windowBounds)
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

void PauseMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	continueGameButton.handleInput(window, event);
	restartLevelButton.handleInput(window, event);
	optionsButton.handleInput(window, event);
	menuButton.handleInput(window, event);
}

void PauseMenu::draw(sf::RenderWindow* window)
{
	// draw the background sprite & title text
	Menu::draw(window);
	
	// draw the buttons
	continueGameButton.draw(window);
	restartLevelButton.draw(window);
	optionsButton.draw(window);
	menuButton.draw(window);
}

bool PauseMenu::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/PauseMenu_Blue.png"))
	{
		return false;
	}

	sf::Vector2f backgroundPosition = getCenter(gameBounds);
	setupSprite(&backgroundSprite, &backgroundTexture, sf::Vector2f(1.5, 1.5), backgroundPosition);

	return true;
}

bool PauseMenu::initializeText()
{
	sf::Vector2f textPosition;
	textPosition.x = getCenter(backgroundSprite.getGlobalBounds()).x;
	textPosition.y = backgroundSprite.getGlobalBounds().top + (titleText.getLocalBounds().height / 2) + 25;

	setupText(&titleText, "Paused", 35, textPosition);

	return true;
}

bool PauseMenu::initializeButtons()
{
	float buttonX = backgroundSprite.getGlobalBounds().width / 2;

	continueGameButton = BlueButton(sf::Vector2f(buttonX, 100), "Continue");
	restartLevelButton = BlueButton(sf::Vector2f(buttonX, 180), "Restart");
	optionsButton = BlueButton(sf::Vector2f(buttonX, 260), "Options");
	menuButton = RedButton(sf::Vector2f(buttonX, 340), "Main Menu");

	if (!continueGameButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!restartLevelButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!optionsButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!menuButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	return false;
}
