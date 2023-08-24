#include "Game.h"

int main()
{
	Game game = Game();

	if (!game.initialize())
	{
		return 1;
	}

	game.run();
	return 0;
}