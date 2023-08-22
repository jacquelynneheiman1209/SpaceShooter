#include "Game.h"
#include <iostream>

Game::Game() : background(windowWidth, windowHeight)
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

	return true;
}

void Game::run()
{
	windowWidth = (sf::VideoMode::getDesktopMode().width / 3) * 2;
	windowHeight = (sf::VideoMode::getDesktopMode().height / 3) * 2;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Shooter");

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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		update(deltaTime);
		draw(&window);
	}
}

void Game::update(float deltaTime)
{

}

void Game::draw(sf::RenderWindow* window)
{
	window->clear();

	// draw things here
	background.draw(window);

	window->display();
}

bool Game::loadBackground()
{
	

	return background.initialize();
}
