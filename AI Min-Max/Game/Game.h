#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "SearchSpace.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

class Game
{
	enum class CurrentPlayer
	{
		HUMAN,
		AI
	};

public:

	// deleted copy assignment operator.
	Game(const Game&) = delete;

	// deleted assignment operator.
	const Game& operator = (const Game&) = delete;

	// destructor.
	~Game();

	//------> Public functions <-----//

	// start game.
	static void StartGame();

	// checks if game is over.
	static bool GameOver();

	// Play the game.
	static void PlayGame();

	// end game.
	static void EndGame();

	// player exit
	static void PlayerExit();

	//-------------------------------//

private:

	//------> Private functions <-----//

	// singleton class instance.
	static Game* privGetInstance();

	// private default constructor.
	Game();

	// check score of players.
	void CheckScore();

	//-------------------------------//

	//------> Data <-----//
	
	// Main game board
	Board* mainBoard;

	// current player
	CurrentPlayer player;

	// human
	HumanPlayer* humanPlayer;

	// ai
	AIPlayer* aiPlayer;

	// did player quit?
	bool playerExit;

	//-------------------//
};

#endif GAME_H