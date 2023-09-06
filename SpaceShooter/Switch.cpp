#include "Switch.h"
#include "Debug.h"

Switch::Switch(sf::Vector2f position, std::string textString, sf::FloatRect parentBounds)
{
	this->position = position;
	this->textString = textString;
	this->parentBounds = parentBounds;
}

bool Switch::initialize(sf::FloatRect parentBounds)
{
	if (this->parentBounds != parentBounds)
	{
		this->parentBounds = parentBounds;
	}

	if (!onTexture.loadFromFile("Assets/Graphics/UI/dotGreen.png"))
	{
		return false;
	}

	if (!offTexture.loadFromFile("Assets/Graphics/UI/dotRed.png"))
	{
		return false;
	}

	switchSprite.setTexture(offTexture);
	switchSprite.setOrigin(switchSprite.getLocalBounds().left + (switchSprite.getLocalBounds().width / 2), switchSprite.getLocalBounds().top + (switchSprite.getLocalBounds().height / 2));
	switchSprite.setPosition(position);

	regularRotation = switchSprite.getRotation();
	hoverRotation = regularRotation + 180;

	if (!font.loadFromFile("Assets/Fonts/nulshock.otf"))
	{
		return false;
	}

	text.setFont(font);
	text.setString(textString);
	text.setCharacterSize(22);
	text.setFillColor(sf::Color(161, 166, 174));
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2), text.getLocalBounds().top + (text.getLocalBounds().height / 2));
	text.setPosition(switchSprite.getPosition().x + (switchSprite.getGlobalBounds().width / 2) + (text.getLocalBounds().width / 2) + textSpacing, switchSprite.getPosition().y);

	return true;
}

void Switch::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (isMouseOver(sf::Mouse::getPosition(*window)))
	{
		switchSprite.setRotation(regularRotation);

		if (event->type == sf::Event::MouseButtonPressed)
		{
			if (value == true)
			{
				value = false;
				switchSprite.setTexture(offTexture);
			}
			else
			{
				value = true;
				switchSprite.setTexture(onTexture);
			}
		}

	}
	else
	{
		switchSprite.setRotation(hoverRotation);
	}
}

void Switch::draw(sf::RenderWindow* window)
{
	window->draw(switchSprite);
	window->draw(text);
}

sf::FloatRect Switch::getLocalBounds()
{
	float width = switchSprite.getGlobalBounds().width + text.getGlobalBounds().width + textSpacing;;
	float height;

	float diffHeight = switchSprite.getGlobalBounds().height - text.getGlobalBounds().height;

	if (diffHeight >= 0)
	{
		height = switchSprite.getGlobalBounds().height;
	}
	else
	{
		height = text.getGlobalBounds().height;
	}

	return sf::FloatRect(0, 0, width, height);
}

sf::FloatRect Switch::getGlobalBounds()
{
	float left = switchSprite.getGlobalBounds().left;
	float top;

	float heightDiff = switchSprite.getGlobalBounds().height - text.getGlobalBounds().height;

	if (heightDiff >= 0)
	{
		top = switchSprite.getGlobalBounds().top;
	}
	else
	{
		top = text.getGlobalBounds().top;
	}

	return sf::FloatRect(left, top, getLocalBounds().width, getLocalBounds().height);
}

sf::Vector2f Switch::getOrigin()
{
	float x = getLocalBounds().left + (getLocalBounds().width / 2);
	float y = getLocalBounds().top + (getLocalBounds().height / 2);

	return sf::Vector2f(x, y);
}

void Switch::setPosition(float x, float y)
{
	sf::Vector2f currentPosition;
	currentPosition.x = getGlobalBounds().left + (getGlobalBounds().width / 2);
	currentPosition.y = getGlobalBounds().top + (getGlobalBounds().height / 2);

	sf::Vector2f vectorFromSpriteToPosition = switchSprite.getPosition() - currentPosition;

	sf::Vector2f newSpritePosition;
	newSpritePosition.x = x + vectorFromSpriteToPosition.x;
	newSpritePosition.y = y + vectorFromSpriteToPosition.y;

	switchSprite.setPosition(newSpritePosition);

	sf::Vector2f vectorFromTextToPosition = text.getPosition() - currentPosition;

	sf::Vector2f newTextPosition;
	newTextPosition.x = x + vectorFromTextToPosition.x;
	newTextPosition.y = y + vectorFromTextToPosition.y;

	text.setPosition(newTextPosition);
}

void Switch::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

bool Switch::getValue()
{
	return value;
}

bool Switch::isMouseOver(sf::Vector2i mousePosition)
{
	float switchMinX = switchSprite.getGlobalBounds().left;
	float switchMinY = switchSprite.getGlobalBounds().top;

	float switchMaxX = switchSprite.getGlobalBounds().width + switchMinX;
	float switchMaxY = switchSprite.getGlobalBounds().height + switchMinY;

	float mouseX = static_cast<float>(mousePosition.x);
	float mouseY = static_cast<float>(mousePosition.y);

	return mouseX >= switchMinX && mouseX <= switchMaxX && mouseY >= switchMinY && mouseY <= switchMaxY;
}
