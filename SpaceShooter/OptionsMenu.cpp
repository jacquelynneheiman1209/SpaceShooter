#include "OptionsMenu.h"
#include "Debug.h"

OptionsMenu::OptionsMenu() : Menu(), saveButton(sf::Vector2f(0, 0), "Save"), closeButton(sf::Vector2f(0, 0), "Reset"), sfxVolumeSlider(gameBounds, sf::Vector2f(0, 0), "SFX", 0)
{
}

bool OptionsMenu::initialize(sf::FloatRect windowBounds)
{
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

	sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();

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

	sf::Vector2f buttonPosition;
	buttonPosition.x = (backgroundSprite.getGlobalBounds().width / 2) - 75;
	buttonPosition.y = 170;

	saveButton = GreenButton(buttonPosition, "Save");

	if (!saveButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	saveButton.setScale(.8f, .8f);

	buttonPosition.x = (backgroundSprite.getGlobalBounds().width / 2) + 75;

	closeButton = RedButton(buttonPosition, "Close");

	if (!closeButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	closeButton.setScale(.8f, .8f);

	sf::Vector2f sliderPosition;
	sliderPosition.x = backgroundBounds.left + (backgroundBounds.width / 2);
	sliderPosition.y = backgroundBounds.top + 110;

	sfxVolumeSlider = Slider(backgroundSprite.getGlobalBounds(), sliderPosition, "SFX", AudioManager::getSFXVolume());

	if (!sfxVolumeSlider.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	sfxVolumeSlider.setPosition(sliderPosition.x, sliderPosition.y);

	Debug::Log("SFX Volume: " + std::to_string(AudioManager::getSFXVolume()));

	sfxVolumeSlider.setValue(AudioManager::getSFXVolume() / 10);

	sliderPosition.y = backgroundBounds.top + 180;

	return true;
}

void OptionsMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (AudioManager::getSFXVolume() != sfxVolumeSlider.getValue())
	{
		AudioManager::setSFXVolume(sfxVolumeSlider.getValue() * 10);
	}

	sfxVolumeSlider.handleInput(window, event);
	saveButton.handleInput(window, event);
	closeButton.handleInput(window, event);
}

void OptionsMenu::draw(sf::RenderWindow* window)
{
	// draw background sprite & title text
	Menu::draw(window);

	sfxVolumeSlider.draw(window);
	saveButton.draw(window);
	closeButton.draw(window);
}

bool OptionsMenu::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/optionsMenu_background.png"))
	{
		return false;
	}

	sf::Vector2f position = getCenter(gameBounds);
	position.y -= 50;

	setupSprite(&backgroundSprite, &backgroundTexture, sf::Vector2f(1, 1), position);

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
