#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background
{
public:
	Background(int width, int height);

	bool initialize();
	bool resize(int width, int height);

	void draw(sf::RenderWindow* window);
	
private:
	sf::Texture backgroundTexture;

	int backgroundWidth = 0;
	int backgroundHeight = 0;

	int backgroundTileWidth = 256;
	int backgroundTileHeight = 256;

	std::vector<sf::Sprite> backgroundTiles;
};

#endif // !BACKGROUND_H


