#include "AudioManager.h"
#include <assert.h>

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	assert(instance == nullptr);
	instance = this;

	Load();
}

void AudioManager::adjustMusicVolume(int amount)
{
	instance->musicVolume = instance->setVolume(instance->musicVolume + amount);
}

void AudioManager::adjustSFXVolume(int amount)
{
	instance->sfxVolume = instance->setVolume(instance->sfxVolume + amount);
}

void AudioManager::setMusicVolume(int newVolume)
{
	instance->musicVolume = instance->setVolume(newVolume);
}

void AudioManager::setSFXVolume(int newVolume)
{
	instance->sfxVolume = instance->setVolume(newVolume);
}

int AudioManager::getMusicVolume()
{
	return instance->musicVolume;
}

int AudioManager::getSFXVolume()
{
	return instance->sfxVolume;
}

int AudioManager::setVolume(int volume)
{
	if (volume < instance->minVolume)
	{
		return instance->minVolume;
	}

	if (volume > instance->maxVolume)
	{
		return instance->maxVolume;
	}

	return volume;
}

void AudioManager::Save()
{
	// add saving logic here
}

void AudioManager::Load()
{
	// placeholder until I add loading logic
	setMusicVolume(instance->maxVolume);
	setSFXVolume(instance->maxVolume);

	// add loading logic here
}
