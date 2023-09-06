#include "MinusButton.h"
#include "Debug.h"

MinusButton::MinusButton(sf::Vector2f position, std::string buttonText) : Button(position, buttonText)
{
}

bool MinusButton::initialize(sf::FloatRect windowSize)
{
	if (!buttonTexture.loadFromFile("Assets/Graphics/UI/MinusButton_Regular.png"))
	{
		return false;
	}

	if (!buttonHoverTexture.loadFromFile("Assets/Graphics/UI/MinusButton_Pressed.png"))
	{
		return false;
	}

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setOrigin(getCenter(buttonSprite.getLocalBounds()));
	buttonSprite.setPosition(windowSize.left + buttonPosition.x, windowSize.top + buttonPosition.y);

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

	return true;
}

void MinusButton::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isMouseOver(sf::Mouse::getPosition(*window)))
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

void MinusButton::draw(sf::RenderWindow* window)
{
	window->draw(buttonSprite);
}

bool MinusButton::isMouseOver(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonSprite.getGlobalBounds().left;
	float buttonMinY = buttonSprite.getGlobalBounds().top;

	float buttonMaxX = buttonSprite.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonSprite.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}

void MinusButton::click()
{
	clickedSound.play();
}

sf::Vector2f MinusButton::getSize()
{
	return sf::Vector2f(buttonSprite.getLocalBounds().width, buttonSprite.getLocalBounds().height);
}

sf::FloatRect MinusButton::getBounds()
{
	return buttonSprite.getGlobalBounds();
}

sf::Vector2f MinusButton::getPosition()
{
	return buttonSprite.getPosition();
}

void MinusButton::setPosition(float x, float y)
{
	buttonSprite.setPosition(x, y);
}

void MinusButton::setPosition(sf::Vector2f position)
{
	return setPosition(position.x, position.y);
}

sf::Vector2f MinusButton::getCenter(sf::FloatRect bounds)
{
	return sf::Vector2f(bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2));
}


