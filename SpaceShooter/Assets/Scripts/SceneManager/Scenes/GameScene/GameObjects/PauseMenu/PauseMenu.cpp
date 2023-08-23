#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu() : continueGameButton(sf::Vector2f(0, 0), "Continue"), restartLevelButton(sf::Vector2f(0, 0), "Resume"), optionsButton(sf::Vector2f(0, 0), "Options"), quitButton(sf::Vector2f(30, 300), "Quit")
{

}

bool PauseMenu::initialize()
{
	if (!menuBackgroundTexture.loadFromFile("Assets/Graphics/UI/PauseMenu.png"))
	{
		std::cout << "Could not load the pause menu texture..." << std::endl;
		return false;
	}

	menuBackgroundSprite.setTexture(menuBackgroundTexture);
	menuBackgroundSprite.setScale(1.5, 1.5);
	setupSprite(&menuBackgroundSprite, sf::Vector2f(640, 360));

	continueGameButton = PauseMenuButton(sf::Vector2f(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + 100), "Continue");
	restartLevelButton = PauseMenuButton(sf::Vector2f(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + 180), "Restart");
	optionsButton = PauseMenuButton(sf::Vector2f(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + 260), "Options");
	quitButton = PauseMenuQuitButton(sf::Vector2f(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + 340), "Quit");

	if (!font.loadFromFile("Assets/Fonts/kenvector_future.ttf"))
	{
		return false;
	}

	menuTitleText.setFont(font);
	menuTitleText.setString("Paused");
	menuTitleText.setCharacterSize(35);
	menuTitleText.setOrigin(menuTitleText.getLocalBounds().left + (menuTitleText.getLocalBounds().width / 2), menuTitleText.getLocalBounds().top + (menuTitleText.getLocalBounds().height / 2));
	menuTitleText.setPosition(menuBackgroundSprite.getGlobalBounds().left + (menuBackgroundSprite.getGlobalBounds().width / 2), menuBackgroundSprite.getGlobalBounds().top + (menuTitleText.getLocalBounds().height / 2) + 15);

	if (!continueGameButton.initialize())
	{
		return false;
	}

	if (!restartLevelButton.initialize())
	{
		return false;
	}

	if (!optionsButton.initialize())
	{
		return false;
	}

	if (!quitButton.initialize())
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
	quitButton.handleInput(window, event);
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
	quitButton.draw(window);
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
