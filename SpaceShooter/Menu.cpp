#include "Menu.h"

Menu::Menu()
{
}

bool Menu::initialize(sf::FloatRect gameBounds)
{
	this->gameBounds = gameBounds;

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	return true;
}

void Menu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	// called on derrived class
}

void Menu::draw(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);
	window->draw(titleText);
}

void Menu::setupText(sf::Text* text, std::string textString, int characterSize, sf::Vector2f position, sf::Color color)
{
	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(characterSize);
	text->setOrigin(getCenter(text->getLocalBounds()));
	text->setPosition(position);
	text->setFillColor(color);
}

void Menu::setupSprite(sf::Sprite* sprite, sf::Texture* texture,  sf::Vector2f scale, sf::Vector2f position)
{
	sprite->setTexture(*texture);
	sprite->setScale(scale);
	sprite->setOrigin(getCenter(sprite->getLocalBounds()));
	sprite->setPosition(position);
}

sf::Vector2f Menu::getCenter(sf::FloatRect bounds)
{
	sf::Vector2f center;
	center.x = bounds.left + (bounds.width / 2);
	center.y = bounds.top + (bounds.height / 2);

	return center;
}

bool Menu::initializeBackground()
{
	// called on derrived class
	return false;
}

bool Menu::initializeText()
{
	// called on derrived class
	return false;
}

bool Menu::initializeButtons()
{
	// called on derrived class
	return false;
}
