#include "OptionsMenu.h"
#include "Debug.h"

OptionsMenu::OptionsMenu() : Menu(), fullscreenSwitch(sf::Vector2f(0, 0), "", backgroundSprite.getGlobalBounds()), saveButton(sf::Vector2f(0, 0), "Save"), resetButton(sf::Vector2f(0, 0), "Reset"), sfxVolumeSlider(gameBounds, sf::Vector2f(0, 0)), musicVolumeSlider(gameBounds, sf::Vector2f(0, 0))
{
}

bool OptionsMenu::initialize(sf::FloatRect windowBounds)
{
	Debug::Log("Initializing Options Menu...");

	// initializes the font and saves windowBounds
	if (!Menu::initialize(windowBounds))
	{
		Debug::Log("Failed to initialize options menu base class...");
		return false;
	}

	// setup the menu background
	if (!initializeBackground())
	{
		Debug::Log("Failed to initialize options menu background....");
		return false;
	}

	fullscreenSwitch = Switch(sf::Vector2f(backgroundSprite.getGlobalBounds().left + 50, backgroundSprite.getGlobalBounds().top + 100), "Full Screen", backgroundSprite.getGlobalBounds());

	if (!fullscreenSwitch.initialize(backgroundSprite.getGlobalBounds()))
	{
		Debug::Log("Failed to initialize options menu switch...");
		return false;
	}

	// setup the text on the menu
	if (!initializeText())
	{
		Debug::Log("Failed to initialize options menu text...");
		return false;
	}

	// setup the buttons on the menu
	if (!initializeButtons())
	{
		Debug::Log("Failed to initialize options menus buttons...");
		return false;
	}

	saveButton = GreenButton(sf::Vector2f((backgroundSprite.getGlobalBounds().width / 2) - 75, 325), "Save");

	if (!saveButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	saveButton.setScale(.8f, .8f);

	resetButton = RedButton(sf::Vector2f((backgroundSprite.getGlobalBounds().width / 2) + 75, 325), "Close");

	if (!resetButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	resetButton.setScale(.8f, .8f);

	sfxVolumeSlider = Slider(backgroundSprite.getGlobalBounds(), sf::Vector2f(50, 100));

	if (!sfxVolumeSlider.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	musicVolumeSlider = Slider(backgroundSprite.getGlobalBounds(), sf::Vector2f(50, 200));

	if (!musicVolumeSlider.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	sfxVolumeSlider.setPosition(backgroundSprite.getGlobalBounds().left + (backgroundSprite.getGlobalBounds().height /2), backgroundSprite.getGlobalBounds().top + 200);
	musicVolumeSlider.setPosition(backgroundSprite.getGlobalBounds().left + (backgroundSprite.getGlobalBounds().height / 2), backgroundSprite.getGlobalBounds().top + 250);

	return true;
}

void OptionsMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	sfxVolumeSlider.handleInput(window, event);
	musicVolumeSlider.handleInput(window, event);

	fullscreenSwitch.handleInput(window, event);
	saveButton.handleInput(window, event);
	resetButton.handleInput(window, event);
}

void OptionsMenu::draw(sf::RenderWindow* window)
{
	// draw background sprite & title text
	Menu::draw(window);

	sfxVolumeSlider.draw(window);
	musicVolumeSlider.draw(window);

	fullscreenSwitch.draw(window);
	saveButton.draw(window);
	resetButton.draw(window);
}

bool OptionsMenu::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/optionsMenu_background.png"))
	{
		return false;
	}

	setupSprite(&backgroundSprite, &backgroundTexture, sf::Vector2f(1, 1), getCenter(gameBounds));

	return true;
}

bool OptionsMenu::initializeText()
{
	setupText(&titleText, "Options", 30, sf::Vector2f(backgroundSprite.getPosition().x, backgroundSprite.getGlobalBounds().top + 30));

	return true;
}

bool OptionsMenu::initializeButtons()
{
	return true;
}
