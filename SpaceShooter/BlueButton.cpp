#include "BlueButton.h"
#include <iostream>
#include "Debug.h"

BlueButton::BlueButton(sf::Vector2f position, std::string text) : Button(position, text)
{
}

bool BlueButton::initialize(sf::FloatRect windowBounds)
{
	// set up background sprite for button
	if (!buttonTexture.loadFromFile("Assets/Graphics/UI/buttonBlue_Regular.png"))
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

	// set up the hover background for the button
	if (!buttonHoverTexture.loadFromFile("Assets/Graphics/UI/buttonBlue_Pressed.png"))
	{
		return false;
	}

	// setup hover sound for button
	if (!hoverSoundBuffer.loadFromFile("Assets/Audio/ButtonClick_2.mp3"))
	{
		return false;
	}

	hoverSound.setBuffer(hoverSoundBuffer);

	// setup click sound for button
	if (!clickedSoundBuffer.loadFromFile("Assets/Audio/ButtonClick_1.mp3"))
	{
		return false;
	}

	clickedSound.setBuffer(clickedSoundBuffer);

	// setup button text
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

void BlueButton::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isClicked(sf::Mouse::getPosition(*window)))
	{
		buttonSprite.setTexture(buttonHoverTexture);

		if (!isMouseOverButton)
		{
			hoverSound.play();
			isMouseOverButton = true;
		}
	}
	else
	{
		buttonSprite.setTexture(buttonTexture);
		isMouseOverButton = false;
	}
}

void BlueButton::draw(sf::RenderWindow* window)
{
	window->draw(buttonSprite);
	window->draw(text);
}

bool BlueButton::isClicked(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonSprite.getGlobalBounds().left;
	float buttonMinY = buttonSprite.getGlobalBounds().top;

	float buttonMaxX = buttonSprite.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonSprite.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}

void BlueButton::setScale(float scaleX, float scaleY)
{
	buttonSprite.setScale(scaleX, scaleY);
}

void BlueButton::setScale(sf::Vector2f scale)
{
	setScale(scale.x, scale.y);
}

void BlueButton::click()
{
	clickedSound.play();
}

sf::Vector2f BlueButton::getScale()
{
	return buttonSprite.getScale();
}
