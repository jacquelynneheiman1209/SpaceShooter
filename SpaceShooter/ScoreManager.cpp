#include "ScoreManager.h"
#include <assert.h>
#include <iostream>

ScoreManager* ScoreManager::instance = nullptr;

ScoreManager::ScoreManager()
{
	assert(instance == nullptr);
	instance = this;

	score = 0;
	hiScore = 0;
}

void ScoreManager::setScore(int score)
{
	instance->score = score;

	if (instance->score > instance->hiScore)
	{
		instance->hiScore = instance->score;
	}
}

void ScoreManager::setHiScore(int hiScore)
{
	instance->hiScore = hiScore;
	std::cout << "High Score: " << instance->hiScore << std::endl;
}

int ScoreManager::getScore()
{
	return instance->score;
}

int ScoreManager::getHiScore()
{
	return instance->hiScore;
}

