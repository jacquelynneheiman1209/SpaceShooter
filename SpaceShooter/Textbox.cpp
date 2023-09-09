#include "Textbox.h"

Textbox::Textbox(std::string value, int characterSize, sf::Vector2f position)
{
	this->value = value;
	this->characterSize = characterSize;
	this->position = position;
}

bool Textbox::initialize()
{
	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	text.setFont(font);
	text.setCharacterSize(characterSize);
	setText(this->value);
	setOrigin();
	setPosition(this->position);

	return true;
}

void Textbox::setText(std::string value)
{
	text.setString(value);
	setOrigin();
}

void Textbox::setPosition(sf::Vector2f position)
{
	this->position = position;
	text.setPosition(position);
}

void Textbox::draw(sf::RenderWindow* window)
{
	window->draw(text);
}

void Textbox::setOrigin()
{
	sf::FloatRect textBounds = text.getLocalBounds();
	
	sf::Vector2f origin;
	origin.x = textBounds.left + (textBounds.width / 2);
	origin.y = textBounds.top + (textBounds.height / 2);

	text.setOrigin(origin);
}
