#include "PlusButton.h"
#include "Debug.h"

PlusButton::PlusButton(sf::Vector2f position, std::string buttonText) : Button(position, buttonText)
{
}

bool PlusButton::initialize(sf::FloatRect windowSize)
{
	if (!buttonTexture.loadFromFile("Assets/Graphics/UI/PlusButton_Regular.png"))
	{
		return false;
	}

	if (!buttonHoverTexture.loadFromFile("Assets/Graphics/UI/PlusButton_Pressed.png"))
	{
		return false;
	}

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setOrigin(getCenter(buttonSprite.getLocalBounds()));
	buttonSprite.setPosition(windowSize.left + buttonPosition.x, windowSize.top + buttonPosition.y);

	return true;
}

void PlusButton::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isMouseOver(sf::Mouse::getPosition(*window)))
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

void PlusButton::draw(sf::RenderWindow* window)
{
	window->draw(buttonSprite);
}

bool PlusButton::isMouseOver(sf::Vector2i mousePosition)
{
	float buttonMinX = buttonSprite.getGlobalBounds().left;
	float buttonMinY = buttonSprite.getGlobalBounds().top;

	float buttonMaxX = buttonSprite.getGlobalBounds().width + buttonMinX;
	float buttonMaxY = buttonSprite.getGlobalBounds().height + buttonMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= buttonMinX && mouseX <= buttonMaxX && mouseY >= buttonMinY && mouseY <= buttonMaxY;
}

void PlusButton::click()
{
	AudioManager::Play(AudioManager::SoundType::ButtonClicked);
}

sf::Vector2f PlusButton::getSize()
{
	return sf::Vector2f(buttonSprite.getLocalBounds().width, buttonSprite.getLocalBounds().height);
}

sf::Vector2f PlusButton::getPosition()
{
	return buttonSprite.getPosition();
}

void PlusButton::setPosition(float x, float y)
{
	buttonSprite.setPosition(x, y);
}

void PlusButton::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

sf::FloatRect PlusButton::getBounds()
{
	return buttonSprite.getGlobalBounds();
}

sf::Vector2f PlusButton::getCenter(sf::FloatRect bounds)
{
	return sf::Vector2f(bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2));
}