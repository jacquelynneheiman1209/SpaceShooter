#pragma once
#include "AudioManager.h"
#include "ScoreManager.h"
#include <string>
#include <vector>

#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

class SaveManager
{
public:
	SaveManager();

	static void Save();
	static void Load();

protected:
	std::string fileName = "save.txt";
	static SaveManager* instance;

};

#endif // !SAVE_MANAGER_H



