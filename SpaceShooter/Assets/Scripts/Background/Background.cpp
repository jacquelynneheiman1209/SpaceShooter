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

	//std::cout << "Num Tiles Wide: " << numTilesWide << std::endl;
	//std::cout << "Num Tiles High: " << numTilesHigh << std::endl;

	//std::cout << "Total Num Tiles: " << numTilesWide * numTilesHigh << std::endl;
	//std::cout << "------------------------------------------ " << std::endl;

	for (int i = 0; i < numTilesWide * numTilesHigh; i++)
	{
		backgroundTiles.push_back(sf::Sprite(backgroundTexture));
	}

	for (int y = 0; y < numTilesHigh; y++)
	{
		for (int x = 0; x < numTilesWide; x++)
		{
			sf::Vector2f tilePosition;
			tilePosition.x = x * backgroundTileWidth;
			tilePosition.y = y * backgroundTileHeight;

			int backgroundIndex = y * numTilesWide + x;
			backgroundTiles[backgroundIndex].setPosition(tilePosition);

			//std::cout << "------------------------------------------ " << std::endl;
			//std::cout << "Background Index: " << backgroundIndex << std::endl;
			//std::cout << "Tile Position: " << tilePosition.x << ", " << tilePosition.y << std::endl;
			//std::cout << "------------------------------------------ " << std::endl;
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
