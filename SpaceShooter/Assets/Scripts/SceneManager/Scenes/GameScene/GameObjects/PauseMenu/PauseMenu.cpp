#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu()
{

}

bool PauseMenu::initialize()
{
	if (!menuBackgroundTexture.loadFromFile("Assets/Graphics/UI/metalPanel_yellow.png"))
	{
		std::cout << "Could not load the pause menu texture..." << std::endl;
		return false;
	}

	menuBackgroundSprite.setTexture(menuBackgroundTexture);
	menuBackgroundSprite.setScale(menuBackgroundScale);
	setupSprite(&menuBackgroundSprite, sf::Vector2f(640, 360));

	return true;
}

void PauseMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
}

void PauseMenu::update(float deltaTime)
{
}

void PauseMenu::draw(sf::RenderWindow* window)
{
	window->draw(menuBackgroundSprite);
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
