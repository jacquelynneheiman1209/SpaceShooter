#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f position, std::string text)
{
	buttonPosition = position;
	buttonText = text;
}

bool Button::initialize()
{
	if (!buttonTexture.loadFromFile("Assets/Graphics/UI/buttonGreen.png"))
	{
		return false;
	}

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setOrigin(buttonSprite.getLocalBounds().left + (buttonSprite.getLocalBounds().width / 2), buttonSprite.getLocalBounds().top + (buttonSprite.getLocalBounds().height / 2));
	buttonSprite.setPosition(buttonPosition);

	if (!font.loadFromFile("Assets/Fonts/kenvector_future.ttf"))
	{
		return false;
	}

	text.setFont(font);
	text.setString(buttonText);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2), text.getLocalBounds().top + (text.getLocalBounds().height / 2));
	text.setPosition((buttonSprite.getGlobalBounds().left + (buttonSprite.getGlobalBounds().width / 2)), (buttonSprite.getGlobalBounds().top + (buttonSprite.getGlobalBounds().height / 2)));

	return true;
}

void Button::update(float deltaTime)
{

}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(buttonSprite);
	window->draw(text);
}

bool Button::isClicked(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonSprite.getGlobalBounds().left;
	float buttonMinY = buttonSprite.getGlobalBounds().top;

	float buttonMaxX = buttonSprite.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonSprite.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}
