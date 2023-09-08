#include "OptionsMenu.h"
#include "Debug.h"

OptionsMenu::OptionsMenu() : Menu(), fullscreenSwitch(sf::Vector2f(0, 0), "", backgroundSprite.getGlobalBounds()), saveButton(sf::Vector2f(0, 0), "Save"), closeButton(sf::Vector2f(0, 0), "Reset"), sfxVolumeSlider(gameBounds, sf::Vector2f(0, 0), "SFX", 0), musicVolumeSlider(gameBounds, sf::Vector2f(0, 0), "Music", 0)
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

	fullscreenSwitch = Switch(sf::Vector2f(backgroundSprite.getGlobalBounds().left + 50, backgroundSprite.getGlobalBounds().top + 230), "Full Screen", backgroundSprite.getGlobalBounds());

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

	closeButton = RedButton(sf::Vector2f((backgroundSprite.getGlobalBounds().width / 2) + 75, 325), "Close");

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

	musicVolumeSlider = Slider(backgroundSprite.getGlobalBounds(), sliderPosition, "Music", AudioManager::getMusicVolume());

	if (!musicVolumeSlider.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	musicVolumeSlider.setPosition(sliderPosition.x, sliderPosition.y);
	musicVolumeSlider.setValue(AudioManager::getMusicVolume() / 10);

	return true;
}

void OptionsMenu::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (AudioManager::getSFXVolume() != sfxVolumeSlider.getValue())
	{
		AudioManager::setSFXVolume(sfxVolumeSlider.getValue() * 10);
	}

	if (AudioManager::getMusicVolume() != musicVolumeSlider.getValue())
	{
		AudioManager::setMusicVolume(musicVolumeSlider.getValue() * 10);
	}

	sfxVolumeSlider.handleInput(window, event);
	musicVolumeSlider.handleInput(window, event);

	fullscreenSwitch.handleInput(window, event);
	saveButton.handleInput(window, event);
	closeButton.handleInput(window, event);
}

void OptionsMenu::draw(sf::RenderWindow* window)
{
	// draw background sprite & title text
	Menu::draw(window);

	sfxVolumeSlider.draw(window);
	musicVolumeSlider.draw(window);

	fullscreenSwitch.draw(window);
	saveButton.draw(window);
	closeButton.draw(window);
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
