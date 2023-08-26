#include "Debug.h"
#include <assert.h>

Debug* Debug::instance = nullptr;

Debug::Debug()
{
	assert(instance == nullptr);
	instance = this;
}

void Debug::Log(std::string message)
{
	std::cout << message << std::endl;
}
