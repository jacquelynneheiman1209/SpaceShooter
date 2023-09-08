#include "SaveManager.h"
#include "Debug.h"
#include <assert.h>
#include <iostream>
#include <fstream>

SaveManager* SaveManager::instance = nullptr;

SaveManager::SaveManager()
{
	assert(instance == nullptr);
	instance = this;
}

void SaveManager::Save()
{
	int sfxVolume = AudioManager::getSFXVolume();
	int musicVolume = AudioManager::getMusicVolume();

	int score = ScoreManager::getScore();
	int hiScore = ScoreManager::getHiScore();

	std::string saveData = "";
	saveData += std::to_string(sfxVolume) + "\n";
	saveData += std::to_string(musicVolume) + "\n";
	saveData += std::to_string(score) + "\n";
	saveData += std::to_string(hiScore) + "\n";

	std::fstream saveFile;
	saveFile.open("save.txt", std::fstream::in | std::fstream::out);
	saveFile << saveData << "\n";
	saveFile.close();
}

void SaveManager::Load()
{
	std::ifstream saveFile("save.txt");
	std::vector<std::string> values;

	while (!saveFile.eof())
	{
		std::string line;
		saveFile >> line;
		values.push_back(line);
	}

	if (values.size() > 3)
	{
		AudioManager::setSFXVolume(std::stoi(values[0]));
		AudioManager::setMusicVolume(std::stoi(values[1]));
		ScoreManager::setScore(std::stoi(values[2]));
		ScoreManager::setHiScore(std::stoi(values[3]));
	}
	else
	{
		Debug::Log("Could not load values...");
	}
}