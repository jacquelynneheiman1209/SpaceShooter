#include "Background.h"
#include <iostream>

Background::Background(int width, int height)
{
	backgroundWidth = width;
	backgroundHeight = height;
}

bool Background::initialize()
{
	if (!backgroundTexture.loadFromFile("Assets/Graphics/Backgrounds/blue.png"))
	{
		return false;
	} 

	resize(backgroundWidth, backgroundHeight);

	return true;
}

bool Background::resize(int width, int height)
{
	backgroundTiles.clear();

	int numTilesWide = (width / backgroundTileWidth) + 1;
	int numTilesHigh = (height / backgroundTileHeight) + 1;

	for (int i = 0; i < numTilesWide * numTilesHigh; i++)
	{
		backgroundTiles.push_back(sf::Sprite(backgroundTexture));
	}

	for (int y = 0; y < numTilesHigh; y++)
	{
		for (int x = 0; x < numTilesWide; x++)
		{
			sf::Vector2f tilePosition;
			tilePosition.x = static_cast<float>(x * backgroundTileWidth);
			tilePosition.y = static_cast<float>(y * backgroundTileHeight);

			int backgroundIndex = y * numTilesWide + x;
			backgroundTiles[backgroundIndex].setPosition(tilePosition);
		}
	}

	return true;
}

void Background::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < backgroundTiles.size(); i++)
	{
		window->draw(backgroundTiles[i]);
	}
}
