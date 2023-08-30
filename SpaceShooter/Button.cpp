#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f position, std::string text)
{
	buttonPosition = position;
	buttonText = text;
}

Button::Button(sf::Vector2f position, std::string text, sf::Color color, sf::Color hoverColor)
{
	buttonPosition = position;
	buttonText = text;
	buttonColor = color;
	buttonHoverColor = hoverColor;
}

bool Button::initialize()
{
	buttonBackground.setSize(sf::Vector2f(200, 40));
	buttonBackground.setFillColor(buttonColor);

	sf::FloatRect buttonBounds = buttonBackground.getLocalBounds();

	buttonBackground.setOrigin(buttonBounds.left + (buttonBounds.width / 2), buttonBounds.top + (buttonBounds.height / 2));
	buttonBackground.setPosition(buttonPosition);

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	text.setFont(font);
	text.setString(buttonText);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2), text.getLocalBounds().top + (text.getLocalBounds().height / 2));
	text.setPosition((buttonBackground.getGlobalBounds().left + (buttonBackground.getGlobalBounds().width / 2)), (buttonBackground.getGlobalBounds().top + (buttonBackground.getGlobalBounds().height / 2)));

	return true;
}

void Button::update(float deltaTime)
{

}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(buttonBackground);
	window->draw(text);
}

void Button::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isMouseOver(sf::Mouse::getPosition(*window)))
	{
		buttonBackground.setFillColor(buttonHoverColor);
	}
	else
	{
		buttonBackground.setFillColor(buttonColor);
	}
}

bool Button::isMouseOver(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonBackground.getGlobalBounds().left;
	float buttonMinY = buttonBackground.getGlobalBounds().top;

	float buttonMaxX = buttonBackground.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonBackground.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}

void Button::setScale(float scaleX, float scaleY)
{
}

void Button::setScale(sf::Vector2f scale)
{
}
