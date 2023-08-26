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

	std::vector<std::unique_ptr<EnemyShip>> enemyShips;
	std::vector<std::unique_ptr<Asteroid>> asteroids;

	bool isPaused = false;
	bool isGameOver = false;
	bool playerWon = false;

	int asteroidPoints = 50;
	int enemyPoints = 200;

	int score = 0;
	int highScore = 0;

	int numAsteroidsSpawned = 0;
	int numAsteroidsAllowedInScene = 3;

	int numEnemiesShipsSpawned = 0;
	int numEnemiesAllowedInScene = 1;

	float asteroidSpawnTimer = 0;
	float asteroidSpawnDelay = 1;

	float enemySpawnTimer = 0;
	float minEnemyShipSpawnDelay = 10;		// in seconds
	float maxEnemyShipSpawnDelay = 40;		// in seconds
	float enemySpawnDelay = 1;

	bool canSpawnAsteroid = false;
	bool canSpawnEnemy = false;

	bool initializeAsteroids();
	bool initializeEnemyShips();

	int getNextAsteroidIndex();
	int getNextEnemyShipIndex();

};

#endif // !GAME_SCENE_H



