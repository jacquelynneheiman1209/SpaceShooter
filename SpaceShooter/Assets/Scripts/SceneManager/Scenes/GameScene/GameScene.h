#pragma once
#include <SFML/Graphics.hpp>
#include "../Scene.h"
#include "../../../UI Elements/Button/Button.h"
#include "../../SceneLoader.h"
#include "GameObjects/Player/Player.h"


#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class GameScene : public Scene
{
public:
	GameScene(SceneLoader* sceneLoader);

	bool initialize() override;

	void handleInput(sf::RenderWindow* window, sf::Event* event);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow* window) override;

private:
	SceneLoader* sceneLoader;

	Player player;

	bool isPaused;
};

#endif // !GAME_SCENE_H



