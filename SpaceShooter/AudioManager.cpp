#include "AudioManager.h"
#include "Debug.h"
#include <assert.h>

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	assert(instance == nullptr);
	instance = this;

	Load();
}

bool AudioManager::initialize()
{
	if (!instance->buttonHoverSoundBuffer.loadFromFile("Assets/Audio/ButtonClick_2.mp3"))
	{
		Debug::Log("AudioManager.cpp : Could not load 'buttonHoverSoundBuffer' from 'Assets/Audio/ButtonClick_2.mp3'");
		return false;
	}

	instance->buttonHoverSound.setBuffer(instance->buttonHoverSoundBuffer);

	if (!instance->buttonClickedSoundBuffer.loadFromFile("Assets/Audio/ButtonClick_1.mp3"))
	{
		Debug::Log("AudioManager.cpp : Could not load 'buttonClickSoundBuffer' from 'Assets/Audio/ButtonClick_1.mp3'");
		return false;
	}

	instance->buttonClickedSound.setBuffer(instance->buttonClickedSoundBuffer);

	if (!instance->shootSoundBuffer.loadFromFile("Assets/Audio/sfx_laser1.ogg"))
	{
		Debug::Log("AudioManager.cpp : Could not load 'shootSoundBuffer' from 'Assets/Audio/sfx_laser1.ogg'");
		return false;
	}

	instance->shootSound.setBuffer(instance->shootSoundBuffer);

	if (!instance->destroySoundBuffer.loadFromFile("Assets/Audio/sfx_twoTone.ogg"))
	{
		Debug::Log("AudioManager.cpp : Could not load 'destroySoundBuffer' from 'Assets/Audio/sfx_twoTone.ogg'");
		return false;
	}

	instance->destroySound.setBuffer(instance->destroySoundBuffer);

	if (!instance->playerDeathSoundBuffer.loadFromFile("Assets/Audio/sfx_lose.ogg"))
	{
		Debug::Log("AudioManager.cpp : Could not load 'playerDeathSoundBuffer' from 'Assets/Audio/sfx_lose.ogg'");
		return false;
	}

	instance->playerDeathSound.setBuffer(instance->playerDeathSoundBuffer);

	return true;
}

void AudioManager::Play(SoundType soundType)
{
	switch (soundType)
	{
	case AudioManager::ButtonHover:
		instance->PlayButtonHoverSound();
		break;
	case AudioManager::ButtonClicked:
		instance->PlayButtonClickedSound();
		break;
	case AudioManager::Shoot:
		instance->PlayShootSound();
		break;
	case AudioManager::Destroy:
		instance->PlayDestroySound();
		break;
	case AudioManager::PlayerDeath:
		instance->PlayPlayerDeathSound();
		break;
	default:
		break;
	}
}

void AudioManager::adjustMusicVolume(int amount)
{
	instance->musicVolume = instance->setVolume(instance->musicVolume + amount);
	instance->updateMusic();
}

void AudioManager::adjustSFXVolume(int amount)
{
	instance->sfxVolume = instance->setVolume(instance->sfxVolume + amount);
	instance->updateSFX();
}

void AudioManager::setMusicVolume(int newVolume)
{
	instance->musicVolume = instance->setVolume(newVolume);
	instance->updateMusic();
}

void AudioManager::setSFXVolume(int newVolume)
{
	instance->sfxVolume = instance->setVolume(newVolume);
	instance->updateSFX();
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

void AudioManager::updateMusic()
{
	instance->musicSound.setVolume(static_cast<float>(instance->musicVolume));
}

void AudioManager::PlayMusic()
{
	// play background music here
}

void AudioManager::updateSFX()
{
	instance->buttonHoverSound.setVolume(static_cast<float>(instance->sfxVolume));
	instance->buttonClickedSound.setVolume(static_cast<float>(instance->sfxVolume));
	instance->shootSound.setVolume(static_cast<float>(instance->sfxVolume));
	instance->destroySound.setVolume(static_cast<float>(instance->sfxVolume));
}

void AudioManager::PlayButtonHoverSound()
{
	buttonHoverSound.play();
}

void AudioManager::PlayButtonClickedSound()
{
	buttonClickedSound.play();
}

void AudioManager::PlayShootSound()
{
	shootSound.play();
}

void AudioManager::PlayDestroySound()
{
	destroySound.play();
}

void AudioManager::PlayPlayerDeathSound()
{
	playerDeathSound.play();
}
