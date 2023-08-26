#include "Game.h"
#include "Debug.h"

Debug debugger;

int main()
{
	srand(time(0));

	Game game = Game();

	if (!game.initialize())
	{
		return 1;
	}

	game.run();
	return 0;
}