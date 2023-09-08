#pragma once
#include "SaveManager.h"

#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

class ScoreManager
{
public:
	ScoreManager();

	static void setScore(int score);
	static void setHiScore(int hiScore);

	static int getScore();
	static int getHiScore();

private:
	static ScoreManager* instance;

	int score;
	int hiScore;
};

#endif // !SCORE_MANAGER_H


