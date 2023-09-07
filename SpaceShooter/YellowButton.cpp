#include "YellowButton.h"
#include <iostream>

YellowButton::YellowButton(sf::Vector2f position, std::string text) : Button(position, text)
{
}

bool YellowButton::initialize(sf::FloatRect windowBounds)
{
    if (!buttonTexture.loadFromFile("Assets/Graphics/UI/buttonYellow_Regular.png"))
    {
        return false;
    }

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setScale(1.5, 1.5);
	buttonSprite.setOrigin(buttonSprite.getLocalBounds().left + (buttonSprite.getLocalBounds().width / 2), buttonSprite.getLocalBounds().top + (buttonSprite.getLocalBounds().height / 2));

	float positionX = buttonPosition.x;
	float positionY = buttonPosition.y;

	buttonPosition.x = windowBounds.left + buttonPosition.x;
	buttonPosition.y = windowBounds.top + buttonPosition.y;

	buttonSprite.setPosition(buttonPosition);

	if (!buttonHoverTexture.loadFromFile("Assets/Graphics/UI/buttonYellow_Pressed.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setString(buttonText);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2), text.getLocalBounds().top + (text.getLocalBounds().height / 2));
	text.setPosition(buttonPosition);

    return true;
}

void YellowButton::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isClicked(sf::Mouse::getPosition(*window)))
	{
		buttonSprite.setTexture(buttonHoverTexture);

		if (!isMouseOverButton)
		{
			AudioManager::Play(AudioManager::SoundType::ButtonHover);
			isMouseOverButton = true;
		}
	}
	else
	{
		buttonSprite.setTexture(buttonTexture);
		isMouseOverButton = false;
	}
}

void YellowButton::draw(sf::RenderWindow* window)
{
	window->draw(buttonSprite);
	window->draw(text);
}

bool YellowButton::isClicked(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonSprite.getGlobalBounds().left;
	float buttonMinY = buttonSprite.getGlobalBounds().top;

	float buttonMaxX = buttonSprite.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonSprite.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}

void YellowButton::setScale(float scaleX, float scaleY)
{
	buttonSprite.setScale(scaleX, scaleY);
}

void YellowButton::setScale(sf::Vector2f scale)
{
	setScale(scale.x, scale.y);
}

void YellowButton::click()
{
	AudioManager::Play(AudioManager::SoundType::ButtonClicked);
}

sf::Vector2f YellowButton::getScale()
{
	return buttonSprite.getScale();
}
