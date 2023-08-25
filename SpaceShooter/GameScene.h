#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"
#include "SceneLoader.h"
#include "Player.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "PlayerHUD.h"
#include "Asteroid.h"

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class GameScene : public Scene
{
public:
	GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds);

	bool initialize() override;

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;

private:
	SceneLoader* sceneLoader;

	sf::FloatRect gameBounds;

	Player player;
	PauseMenu pauseMenu;
	GameOverMenu gameOverMenu;
	PlayerHUD playerHUD;

	std::vector<std::unique_ptr<Asteroid>> asteroids;

	bool isPaused = false;
	bool isGameOver = false;
	bool playerWon = false;

	int score = 0;
	int highScore = 0;

	int numAsteroidsSpawned = 0;
	int numAsteroidsAllowedInScene = 3;

	bool initializeAsteroids();

};

#endif // !GAME_SCENE_H



