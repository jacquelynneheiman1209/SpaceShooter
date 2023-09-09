#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(SceneLoader* sceneLoader, sf::FloatRect windowSize) : startGameButton(sf::Vector2f(0, 0), "Play"), quitGameButton(sf::Vector2f(0, 0), "Quit"), optionsButton(sf::Vector2f(0, 0), "Options"), highScoreTextbox("High Score 000000", 35, sf::Vector2f(0, 0))
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

	highScoreTextbox = Textbox("High Score " + std::to_string(ScoreManager::getHiScore()), 25, sf::Vector2f(position.x, position.y + 180));

	if (!highScoreTextbox.initialize())
	{
		return false;
	}

	optionsMenu = OptionsMenu();

	if (!optionsMenu.initialize(windowSize))
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
	if (showOptionsMenu)
	{
		if (event->type == sf::Event::MouseButtonPressed)
		{
			if (optionsMenu.saveButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				SaveManager::Save();
				optionsMenu.saveButton.click();
				showOptionsMenu = false;
			}

			if (optionsMenu.closeButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				optionsMenu.closeButton.click();
				showOptionsMenu = false;
			}
		}

		optionsMenu.handleInput(window, event);
	}
	else
	{
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
				showOptionsMenu = true;
			}

			if (quitGameButton.isClicked(sf::Mouse::getPosition(*window)))
			{
				quitGameButton.click();
				SaveManager::Save();
				window->close();
			}
		}
	}
}

void MainMenuScene::draw(sf::RenderWindow* window)
{
	window->draw(gameTitleText);
	startGameButton.draw(window);
	optionsButton.draw(window);
	quitGameButton.draw(window);
	highScoreTextbox.draw(window);

	if (showOptionsMenu)
	{
		optionsMenu.draw(window);
	}
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
