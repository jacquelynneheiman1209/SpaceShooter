#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu() : continueGameButton(sf::Vector2f(0, 0), "Continue"), restartLevelButton(sf::Vector2f(0, 0), "Resume"), optionsButton(sf::Vector2f(0, 0), "Options"), menuButton(sf::Vector2f(0, 0), "Main Menu")
{

}

bool PauseMenu::initialize(sf::FloatRect windowBounds)
{
	if (!menuBackgroundTexture.loadFromFile("Assets/Graphics/UI/PauseMenu_Blue.png"))
	{
		std::cout << "PauseMenu.cpp : Could not load 'menuBackgroundTexture'" << std::endl;
		return false;
	}

	menuBackgroundSprite.setTexture(menuBackgroundTexture);
	menuBackgroundSprite.setScale(1.5, 1.5);
	setupSprite(&menuBackgroundSprite, sf::Vector2f(windowBounds.left + (windowBounds.width / 2), windowBounds.top + (windowBounds.height / 2)));

	sf::Vector2f buttonPosition;
	buttonPosition.x = menuBackgroundSprite.getGlobalBounds().width / 2;

	continueGameButton = BlueButton(sf::Vector2f(buttonPosition.x, 100), "Continue");
	restartLevelButton = BlueButton(sf::Vector2f(buttonPosition.x, 180), "Restart");
	optionsButton = BlueButton(sf::Vector2f(buttonPosition.x, 260), "Options");
	menuButton = RedButton(sf::Vector2f(buttonPosition.x, 340), "Main Menu");

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		std::cout << "PauseMenu.cpp : Could not load 'font'" << std::endl;
		return false;
	}

	menuTitleText.setFont(font);
	menuTitleText.setString("Paused");
	menuTitleText.setCharacterSize(35);
	menuTitleText.setOrigin(menuTitleText.getLocalBounds().left + (menuTitleText.getLocalBounds().width / 2), menuTitleText.getLocalBounds().top + (menuTitleText.getLocalBounds().height / 2));
	menuTitleText.setPosition(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + (menuTitleText.getLocalBounds().height / 2) + 15);

	if (!continueGameButton.initialize(menuBackgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!restartLevelButton.initialize(menuBackgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!optionsButton.initialize(menuBackgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	if (!menuButton.initialize(menuBackgroundSprite.getGlobalBounds()))
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

void PauseMenu::update(float deltaTime)
{
}

void PauseMenu::draw(sf::RenderWindow* window)
{
	window->draw(menuBackgroundSprite);
	window->draw(menuTitleText);
	continueGameButton.draw(window);
	restartLevelButton.draw(window);
	optionsButton.draw(window);
	menuButton.draw(window);
}

void PauseMenu::setupSprite(sf::Sprite* sprite, sf::Vector2f position)
{
	sf::FloatRect spriteBounds = sprite->getLocalBounds();

	sprite->setOrigin(spriteBounds.left + (spriteBounds.width / 2), spriteBounds.top + (spriteBounds.height / 2));
	sprite->setPosition(position);
}

void PauseMenu::setupText(sf::Text* text, sf::Vector2f position, std::string textString)
{
}
