#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(SceneLoader* sceneLoader) : startGameButton(sf::Vector2f(640, 325), "Start Game"), quitGameButton(sf::Vector2f(640, 425), "Quit Game")
{
	this->sceneLoader = sceneLoader;
}

bool MainMenuScene::initialize()
{
	if (!font.loadFromFile("Assets/Fonts/kenvector_future.ttf"))
	{
		return false;
	}

	setupText(&gameTitleText, sf::Vector2f((960 / 3) * 2, 100), "Space Shooter", 50, sf::Color::White, sf::Color::White);

	if (!startGameButton.initialize())
	{
		return false;
	}

	if (!quitGameButton.initialize())
	{
		return false;
	}

	return true;
}

void MainMenuScene::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	// Handles hover effect
	startGameButton.handleInput(window, event);
	quitGameButton.handleInput(window, event);

	// Handle mouse clicks on the buttons
	if (event->type == sf::Event::MouseButtonPressed)
	{
		if (startGameButton.isClicked(sf::Mouse::getPosition(*window)))
		{
			sceneLoader->loadScene("Game");
		}

		if (quitGameButton.isClicked(sf::Mouse::getPosition(*window)))
		{
			window->close();
		}
	}
}

void MainMenuScene::update(float deltaTime)
{

}

void MainMenuScene::draw(sf::RenderWindow* window)
{
	window->draw(gameTitleText);
	startGameButton.draw(window);
	quitGameButton.draw(window);
}

void MainMenuScene::setupText(sf::Text* text, sf::Vector2f position, std::string textValue, int characterSize, sf::Color textFillColor, sf::Color textOutlineColor)
{
	text->setFont(font);
	text->setCharacterSize(characterSize);
	text->setFillColor(textFillColor);
	text->setOutlineColor(textOutlineColor);
	text->setString(textValue);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(position);
}
