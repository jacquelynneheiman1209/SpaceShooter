#pragma once
#include <SFML/Audio.hpp>

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

class AudioManager
{
public:
	AudioManager();
	static void adjustMusicVolume(int amount);
	static void adjustSFXVolume(int amount);
	static void setMusicVolume(int newVolume);
	static void setSFXVolume(int newVolume);

	static int getMusicVolume();
	static int getSFXVolume();

	static void Save();

protected:
	static AudioManager* instance;

	int minVolume = 0;
	int maxVolume = 100;

	int musicVolume;
	int sfxVolume;

	sf::SoundBuffer buttonHoverSoundBuffer;
	sf::SoundBuffer buttonClickedSoundBuffer;

	int setVolume(int volume);
	void Load();
};

#endif // !AUDIO_MANAGER_H



