#pragma once
#include <iostream>
#include <string>

#ifndef DEBUG_H
#define DEBUG_H

class Debug
{
public:
	Debug();

	static void Log(std::string message);

private:
	static Debug* instance;
};

#endif // !DEBUG_H



