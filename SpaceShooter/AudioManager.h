#pragma once
#include <SFML/Audio.hpp>

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

class AudioManager
{
public:
	enum SoundType { ButtonHover, ButtonClicked, Shoot, Destroy, PlayerDeath };
	AudioManager();

	bool initialize();

	static void Play(SoundType soundType);

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

	int setVolume(int volume);
	void Load();

	//music
	sf::SoundBuffer musicSoundBuffer;
	sf::Sound musicSound;

	void updateMusic();
	void PlayMusic();
	

	// sfx 
	int sfxVolume;

	sf::SoundBuffer buttonHoverSoundBuffer;
	sf::SoundBuffer buttonClickedSoundBuffer;
	sf::SoundBuffer shootSoundBuffer;
	sf::SoundBuffer destroySoundBuffer;
	sf::SoundBuffer playerDeathSoundBuffer;

	sf::Sound buttonHoverSound;
	sf::Sound buttonClickedSound;
	sf::Sound shootSound;
	sf::Sound destroySound;
	sf::Sound playerDeathSound;

	void updateSFX();

	void PlayButtonHoverSound();
	void PlayButtonClickedSound();
	void PlayShootSound();
	void PlayDestroySound();
	void PlayPlayerDeathSound();
};

#endif // !AUDIO_MANAGER_H



