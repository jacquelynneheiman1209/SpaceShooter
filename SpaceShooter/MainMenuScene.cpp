#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(SceneLoader* sceneLoader, sf::FloatRect windowSize) : startGameButton(sf::Vector2f(0, 0), "Play"), quitGameButton(sf::Vector2f(0, 0), "Quit"), optionsButton(sf::Vector2f(0, 0), "Options")
{
	this->sceneLoader = sceneLoader;
	this->windowSize = windowSize;
}

bool MainMenuScene::initialize(sf::FloatRect windowBounds)
{
	windowSize = windowBounds;

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	setupText(&gameTitleText, sf::Vector2f(windowSize.width / 2, 100), "Space Shooter", 50, sf::Color::White, sf::Color::White);

	sf::Vector2f position;
	position.x = (windowSize.left + (windowSize.width / 2));
	position.y = (windowSize.top + (windowSize.height / 2));

	optionsButton = BlueButton(position, "Options");

	float startButtonPositionY = position.y - 90;
	float quitButtonPositionY = position.y + 90;

	startGameButton = GreenButton(sf::Vector2f(position.x, startButtonPositionY), "Play");
	quitGameButton = RedButton(sf::Vector2f(position.x, quitButtonPositionY), "Quit");

	if (!startGameButton.initialize(windowSize))
	{
		return false;
	}

	if (!optionsButton.initialize(windowSize))
	{
		return false;
	}

	if (!quitGameButton.initialize(windowSize))
	{
		return false;
	}

	return true;
}

void MainMenuScene::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	// Handles hover effect
	startGameButton.handleInput(window, event);
	optionsButton.handleInput(window, event);
	quitGameButton.handleInput(window, event);

	// Handle mouse clicks on the buttons
	if (event->type == sf::Event::MouseButtonPressed)
	{
		if (startGameButton.isClicked(sf::Mouse::getPosition(*window)))
		{
			startGameButton.click();
			sceneLoader->loadScene("Game", windowSize);
		}

		if (optionsButton.isClicked(sf::Mouse::getPosition(*window)))
		{
			optionsButton.click();
			// open options menu
		}

		if (quitGameButton.isClicked(sf::Mouse::getPosition(*window)))
		{
			quitGameButton.click();
			window->close();
		}
	}
}

void MainMenuScene::draw(sf::RenderWindow* window)
{
	window->draw(gameTitleText);
	startGameButton.draw(window);
	optionsButton.draw(window);
	quitGameButton.draw(window);
}

void MainMenuScene::handleWindowResize(sf::FloatRect newWindowSize)
{
	windowSize = newWindowSize;
	initialize(newWindowSize);
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
