#include "ConfirmationMenu.h"
#include "Debug.h"

ConfirmationMenu::ConfirmationMenu() : yesButton(sf::Vector2f(0, 0), "Yes"), noButton(sf::Vector2f(0, 0), "No") 
{

}

bool ConfirmationMenu::initialize(sf::FloatRect windowBounds)
{
	// setup background
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/GameOverMenu_Background.png"))
	{
		Debug::Log("ConfirmationMenu.cpp : Could not load 'backgroundTexture' from 'Assets/Graphics/UI/GameOverMenu_Background.png'");
		return false;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin(getCenter(backgroundSprite.getLocalBounds()));
	backgroundSprite.setPosition(getCenter(windowBounds));

	// setup text
	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	sf::Vector2f textPosition;
	textPosition.x = backgroundSprite.getPosition().x;
	textPosition.y = backgroundBounds.top + 30;

	setText(&titleText, "Are you sure?", 30, textPosition);

	textPosition.y = backgroundSprite.getPosition().y - 20;

	setText(&warningText, "You will lose your progress.", 18, textPosition);

	warningText.setFillColor(sf::Color::Black);

	sf::Vector2f buttonPosition;
	buttonPosition.x = backgroundBounds.left + (backgroundBounds.width / 4);
	buttonPosition.y = backgroundBounds.top + 150;

	// setup buttons
	yesButton = GreenButton(buttonPosition, "Yes");

	buttonPosition.x = backgroundBounds.left + ((backgroundBounds.width / 4) * 3);;

	noButton = RedButton(buttonPosition, "No");

	if (!yesButton.initialize(windowBounds))
	{
		Debug::Log("ConfirmationMenu.cpp : Could not initialize 'yesButton'");
		return false;
	}

	if (!noButton.initialize(windowBounds))
	{
		Debug::Log("ConfirmationMenu.cpp : Could not initialize 'noButton'");
		return false;
	}

	yesButton.setScale(.99f, yesButton.getScale().y);
	noButton.setScale(.99f, noButton.getScale().y);

	return true;
}

void ConfirmationMenu::draw(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);
	window->draw(titleText);
	window->draw(warningText);

	yesButton.draw(window);
	noButton.draw(window);
}

void ConfirmationMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	yesButton.handleInput(window, event);
	noButton.handleInput(window, event);
}

sf::Vector2f ConfirmationMenu::getCenter(sf::FloatRect bounds)
{
	sf::Vector2f origin;
	origin.x = bounds.left + (bounds.width / 2);
	origin.y = bounds.top + (bounds.height / 2);

	return origin;
}

void ConfirmationMenu::setText(sf::Text* text, std::string textString, int characterSize, sf::Vector2f textPosition)
{
	text->setFont(font);
	text->setCharacterSize(characterSize);
	text->setString(textString);
	text->setOrigin(getCenter(text->getLocalBounds()));
	text->setPosition(textPosition);
}
