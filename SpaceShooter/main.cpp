#include "Game.h"
#include "Debug.h"

Debug debugger;

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	Game game = Game();

	if (!game.initialize())
	{
		return 1;
	}

	game.run();
	return 0;
}