#include "Game.h"
#include <iostream>

Game::Game() : background(windowWidth, windowHeight), sceneManager()
{
	windowWidth = (sf::VideoMode::getDesktopMode().width / 3) * 2;
	windowHeight = (sf::VideoMode::getDesktopMode().height / 3) * 2;
}

bool Game::initialize()
{
	if (!loadBackground())
	{
		return false;
	}

	if (!sceneManager.initialize(sf::FloatRect(0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight))))
	{
		return false;
	}

	return true;
}

void Game::run()
{
	windowWidth = (sf::VideoMode::getDesktopMode().width / 3) * 2;
	windowHeight = (sf::VideoMode::getDesktopMode().height / 3) * 2;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Shooter");

	gameView.setCenter(windowWidth / 2, windowHeight / 2);
	gameView.setSize(windowWidth, windowHeight);

	window.setView(gameView);

	while (window.isOpen())
	{
		deltaTime = gameClock.restart().asSeconds();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
				gameView = sf::View(visibleArea);
				window.setView(gameView);

				background.resize(event.size.width, event.size.height);
				sceneManager.handleWindowResize(visibleArea);
			}

			sceneManager.handleInput(&window, &event);
		}

		update(deltaTime);
		draw(&window);
	}
}

void Game::update(float deltaTime)
{
	sceneManager.update(deltaTime);
}

void Game::draw(sf::RenderWindow* window)
{
	window->clear();

	// draw things here
	background.draw(window);
	sceneManager.draw(window);

	window->display();
}

bool Game::loadBackground()
{
	return background.initialize();
}
