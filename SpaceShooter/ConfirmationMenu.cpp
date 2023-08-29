#include "ConfirmationMenu.h"
#include "Debug.h"

ConfirmationMenu::ConfirmationMenu() : yesButton(sf::Vector2f(0, 0), "Yes"), noButton(sf::Vector2f(0, 0), "No") 
{

}

bool ConfirmationMenu::initialize(sf::FloatRect windowBounds)
{
	// setup background sprite & title text
	if (!Menu::initialize(windowBounds))
	{
		return false;
	}

	if (!initializeBackground())
	{
		return false;
	}

	if (!initializeText())
	{
		return false;
	}

	if (!initializeButtons())
	{
		return false;
	}

	return true;
}

void ConfirmationMenu::draw(sf::RenderWindow* window)
{
	// draw background sprite & title text
	Menu::draw(window);

	// draw text
	window->draw(warningText);

	// draw buttons
	yesButton.draw(window);
	noButton.draw(window);
}

void ConfirmationMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	yesButton.handleInput(window, event);
	noButton.handleInput(window, event);
}

bool ConfirmationMenu::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/GameOverMenu_Background.png"))
	{
		return false;
	}

	setupSprite(&backgroundSprite, &backgroundTexture, sf::Vector2f(1, 1), getCenter(gameBounds));

	return true;
}

bool ConfirmationMenu::initializeText()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	sf::Vector2f textPosition;
	textPosition.x = backgroundSprite.getPosition().x;
	textPosition.y = backgroundBounds.top + 30;

	setupText(&titleText, "Are you sure?", 30, textPosition);

	textPosition.y = backgroundSprite.getPosition().y - 20;

	setupText(&warningText, "You will lose your progress.", 18, textPosition, sf::Color::Black);

	return true;
}

bool ConfirmationMenu::initializeButtons()
{
	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

	// setup yes button
	sf::Vector2f buttonPosition;
	buttonPosition.x = backgroundBounds.left + (backgroundBounds.width / 4);
	buttonPosition.y = backgroundBounds.top + 150;

	yesButton = GreenButton(buttonPosition, "Yes");

	if (!yesButton.initialize(gameBounds))
	{
		return false;
	}

	yesButton.setScale(.99f, yesButton.getScale().y);

	// setup no button
	buttonPosition.x = backgroundBounds.left + ((backgroundBounds.width / 4) * 3);;
	noButton = RedButton(buttonPosition, "No");

	if (!noButton.initialize(gameBounds))
	{
		return false;
	}

	noButton.setScale(.99f, noButton.getScale().y);

	return true;
}
