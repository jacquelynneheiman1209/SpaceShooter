#include "PauseMenuQuitButton.h"

PauseMenuQuitButton::PauseMenuQuitButton(sf::Vector2f position, std::string text) : Button(position, text)
{
}

bool PauseMenuQuitButton::initialize()
{
	if (!buttonTexture.loadFromFile("Assets/Graphics/UI/PauseMenu_Button_Red.png"))
	{
		return false;
	}

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setScale(1.5, 1.5);
	buttonSprite.setOrigin(buttonSprite.getLocalBounds().left + (buttonSprite.getLocalBounds().width / 2), buttonSprite.getLocalBounds().top + (buttonSprite.getLocalBounds().height / 2));
	buttonSprite.setPosition(buttonPosition);

	if (!font.loadFromFile("Assets/Fonts/kenvector_future.ttf"))
	{
		return false;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setString(buttonText);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2), text.getLocalBounds().top + (text.getLocalBounds().height / 2));
	text.setPosition(buttonPosition);

	if (!buttonHoverTexture.loadFromFile("Assets/Graphics/UI/PauseMenu_Button_Red_Pressed.png"))
	{
		return false;
	}

	return true;
}

void PauseMenuQuitButton::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isClicked(sf::Mouse::getPosition(*window)))
	{
		buttonSprite.setTexture(buttonHoverTexture);
	}
	else
	{
		buttonSprite.setTexture(buttonTexture);
	}
}
