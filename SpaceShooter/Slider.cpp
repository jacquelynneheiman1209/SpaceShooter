#include "Slider.h"
#include "Debug.h"

Slider::Slider(sf::FloatRect parentBounds, sf::Vector2f position) : plusButton(sf::Vector2f(0, 0), ""), minusButton(sf::Vector2f(0, 0), "")
{
	this->parentBounds = parentBounds;
	this->position = position;
}

bool Slider::initialize(sf::FloatRect parentBounds)
{
	Debug::Log("Initializing Slider");

	if (!backgroundTexture.loadFromFile("Assets/Graphics/UI/volumeBar_shadow.png"))
	{
		return false;
	}

	setupSprite(&backgroundSprite, &backgroundTexture, getCenter(parentBounds));

	if (!fillTexture.loadFromFile("Assets/Graphics/UI/squareGreen.png"))
	{
		return false;
	}

	minusButton = MinusButton(sf::Vector2f(-13 - buttonSpacing, backgroundSprite.getGlobalBounds().height / 2), "");

	if (!minusButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	plusButton = PlusButton(sf::Vector2f(backgroundSprite.getGlobalBounds().width + buttonSpacing + 13, backgroundSprite.getGlobalBounds().height / 2), "");

	if (!plusButton.initialize(backgroundSprite.getGlobalBounds()))
	{
		return false;
	}

	for (int i = 0; i < maxValue; i++)
	{
		std::unique_ptr<sf::Sprite> fillSprite = std::unique_ptr<sf::Sprite>(new sf::Sprite(fillTexture));
		fillSprite.get()->setOrigin(getCenter(fillSprite.get()->getLocalBounds()));
		fillSprite.get()->setPosition((backgroundSprite.getGlobalBounds().left + (fillSprite.get()->getLocalBounds().width / 2)) + (i * 19) + (i * 2), backgroundSprite.getGlobalBounds().top + (backgroundSprite.getGlobalBounds().height / 2));
		fillSprites.push_back(std::move(fillSprite));

		showFillSprites.push_back(true);
	}

	return true;
}

void Slider::handleInput(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == event->MouseButtonPressed)
	{
		if (minusButton.isMouseOver(sf::Mouse::getPosition(*window)))
		{
			decreaseValue();
		}

		if (plusButton.isMouseOver(sf::Mouse::getPosition(*window)))
		{
			increaseValue();
		}
	}

	plusButton.handleInput(window, event);
	minusButton.handleInput(window, event);
}

void Slider::draw(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);

	for (int i = 0; i < maxValue; i++)
	{
		if (showFillSprites[i])
		{
			window->draw(*fillSprites[i].get());
		}
	}

	minusButton.draw(window);
	plusButton.draw(window);
	
}

sf::FloatRect Slider::getLocalBounds()
{
	float width;
	float height;

	width = minusButton.getSize().x + backgroundSprite.getLocalBounds().width + plusButton.getSize().x + (buttonSpacing * 2);
	
	if (minusButton.getSize().y == plusButton.getSize().y)
	{
		if (minusButton.getSize().y > backgroundSprite.getLocalBounds().height)
		{
			height = minusButton.getSize().y;
		}
		else
		{
			height = backgroundSprite.getLocalBounds().height;
		}
	}
	else
	{
		if (minusButton.getSize().y > plusButton.getSize().y)
		{
			if (minusButton.getSize().y > backgroundSprite.getLocalBounds().height)
			{
				height = minusButton.getSize().y;
			}
			else
			{
				height = backgroundSprite.getLocalBounds().height;
			}
		}
		else
		{
			if (plusButton.getSize().y > backgroundSprite.getLocalBounds().height)
			{
				height = plusButton.getSize().y;
			}
			else
			{
				height = backgroundSprite.getLocalBounds().height;
			}
		}
	}

	return sf::FloatRect(0, 0, width, height);

}

sf::FloatRect Slider::getGlobalBounds()
{
	float left = minusButton.getBounds().left;
	float top = minusButton.getBounds().top;

	return sf::FloatRect(left, top, getLocalBounds().width, getLocalBounds().height);
}

void Slider::setPosition(float x, float y)
{
	sf::Vector2f currentPosition = getCenter(getGlobalBounds());

	minusButton.setPosition(x + (minusButton.getPosition() - currentPosition).x, y + (minusButton.getPosition() - currentPosition).y);
	backgroundSprite.setPosition(x + (backgroundSprite.getPosition() - currentPosition).x, y + (backgroundSprite.getPosition() - currentPosition).y);
	plusButton.setPosition(x + (plusButton.getPosition() - currentPosition).x, y + (plusButton.getPosition() - currentPosition).y);

	for (int i = 0; i < maxValue; i++)
	{
		fillSprites[i].get()->setPosition(x + (fillSprites[i].get()->getPosition() - currentPosition).x, y + (fillSprites[i].get()->getPosition() - currentPosition).y);
	}
}

void Slider::setupSprite(sf::Sprite* sprite, sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale)
{
	sprite->setTexture(*texture);

	if (scale != sf::Vector2f(0, 0))
	{
		sprite->setScale(scale);
	}

	sprite->setOrigin(getCenter(sprite->getLocalBounds()));
	sprite->setPosition(position);
}

void Slider::increaseValue()
{
	value++;

	if (value > maxValue)
	{
		value = maxValue;
	}

	showFillSprites[value - 1] = true;
}

void Slider::decreaseValue()
{
	value--;

	if (value < minValue)
	{
		value = minValue;
	}

	showFillSprites[value] = false;
}

sf::Vector2f Slider::getCenter(sf::FloatRect bounds)
{
	return sf::Vector2f(bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2));
}
