#pragma once

#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

class SaveManager
{
public:
	SaveManager();

	void SaveAll();
	void SaveOptions();

protected:
	static SaveManager* instance;

	
};

#endif // !SAVE_MANAGER_H



