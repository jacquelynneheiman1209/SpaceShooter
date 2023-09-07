#include "SaveManager.h"
#include <assert.h>

SaveManager* SaveManager::instance = nullptr;

SaveManager::SaveManager()
{
	assert(instance == nullptr);
	instance = this;
}

void SaveManager::SaveAll()
{

}

void SaveManager::SaveOptions()
{

}
