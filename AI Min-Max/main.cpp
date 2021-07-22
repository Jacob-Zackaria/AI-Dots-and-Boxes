
// user defined classes
#include "Game.h"


// Program start
int main()
{
	// Start game.
	Game::StartGame();

	// Check if game is over.
	while (!Game::GameOver())
	{
		// If not play the game.
		Game::PlayGame();
	}

	// End game.
	Game::EndGame();

	// success
	return 0;
}

