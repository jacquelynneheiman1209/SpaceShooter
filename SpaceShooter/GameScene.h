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
#include "EnemyShip.h"
#include "ConfirmationMenu.h"
#include "OptionsMenu.h"

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class GameScene : public Scene
{
public:
	GameScene(SceneLoader* sceneLoader, sf::FloatRect gameBounds);

	bool initialize(sf::FloatRect windowBounds);

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;

	void handleWindowResize(sf::FloatRect newWindowSize);

private:
	SceneLoader* sceneLoader;

	sf::FloatRect gameBounds;

	Player player;
	PauseMenu pauseMenu;
	GameOverMenu gameOverMenu;
	PlayerHUD playerHUD;

	ConfirmationMenu confirmationMenu;
	OptionsMenu optionsMenu;

	std::vector<std::unique_ptr<EnemyShip>> enemyShips;
	std::vector<std::unique_ptr<Asteroid>> asteroids;

	std::string confirmationReason = "";

	bool showPauseMenu = false;
	bool showConfirmationMenu = false;
	bool showOptionsMenu = true;

	bool isPaused = false;
	bool isGameOver = false;
	bool playerWon = false;

	int asteroidPoints = 50;
	int enemyPoints = 200;

	int numAsteroidsSpawned = 0;
	int numAsteroidsAllowedInScene = 3;
	int numAsteroidsInPool = 10;

	int numEnemiesShipsSpawned = 0;
	int numEnemiesAllowedInScene = 1;
	int numEnemiesInPool = 5;

	float asteroidSpawnTimer = 0;
	float asteroidSpawnDelay = 1;

	float enemySpawnTimer = 0;
	float minEnemyShipSpawnDelay = 10;		// in seconds
	float maxEnemyShipSpawnDelay = 40;		// in seconds
	float enemySpawnDelay = 1;

	bool canSpawnAsteroid = false;
	bool canSpawnEnemy = false;

	int difficultyScoreThreshold = 500;
	int scoreThresholdIncreasePerDifficulty = 500;
	int difficultyLevel = 0;

	bool initializeAsteroids();
	bool initializeEnemyShips();

	int getNextAsteroidIndex();
	int getNextEnemyShipIndex();

	void increaseDifficulty();
	void addScore(int amountToAdd);

	void spawnAsteroid();
	void spawnEnemy();

	void pauseGame();
	void unpauseGame();
	
};

#endif // !GAME_SCENE_H



