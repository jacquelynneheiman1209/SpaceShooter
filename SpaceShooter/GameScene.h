#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../../../UI Elements/Button/Button.h"
#include "../../SceneLoader.h"
#include "GameObjects/Player/Player.h"
#include "GameObjects/PauseMenu/PauseMenu.h"
#include "GameObjects/GameOverMenu/GameOverMenu.h"
#include "GameObjects/HUD/GameHUD.h"

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
	GameHUD hud;

	bool isPaused = false;
	bool isGameOver = false;

	int enemiesKilled = 0;
	int numberEmeniesToKill = 3;
};

#endif // !GAME_SCENE_H



