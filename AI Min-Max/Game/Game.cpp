#include "Game.h"

Game::Game()
	:
	mainBoard(nullptr),
	player(CurrentPlayer::HUMAN),
	humanPlayer(new HumanPlayer()),
	aiPlayer(new AIPlayer()),
	playerExit(false)
{
}

void Game::CheckScore()
{
	// get singleton instance.
	Game* pGame = Game::privGetInstance();

	if (pGame->mainBoard->GetHumanScore() > pGame->mainBoard->GetAIScore())
	{
		printf("\nHUMAN WON!\n");
	}
	else if (pGame->mainBoard->GetHumanScore() == pGame->mainBoard->GetAIScore())
	{
		printf("\nIT'S A DRAW!\n");
	}
	else
	{
		printf("\nAI WON!\n");
	}
}


Game::~Game()
{
}

void Game::StartGame()
{
	// get singleton instance.
	Game* pGame = Game::privGetInstance();

	// Create the main board.
	pGame->mainBoard = new Board();

	// Generate Board.
	pGame->mainBoard->GenerateBoard();

	// Print Board.
	pGame->mainBoard->PrintBoard();

	// Set search settings
	SearchSpace::SetSettings();
}

bool Game::GameOver()
{
	// get singleton instance.
	Game* pGame = Game::privGetInstance();

	// check if all boxes are filled.
	return (pGame->mainBoard->IsFilled() || pGame->playerExit);
}

void Game::PlayGame()
{
	// get singleton instance.
	Game* pGame = Game::privGetInstance();

	if (pGame->player == CurrentPlayer::HUMAN)
	{
		// if player is Human, user marks the line.
		pGame->humanPlayer->Update(*pGame->mainBoard);

		// change current player.
		pGame->player = CurrentPlayer::AI;
	}
	else
	{
		// else player is AI, machine marks the line.
		pGame->aiPlayer->Update(*pGame->mainBoard);

		// change current player.
		pGame->player = CurrentPlayer::HUMAN;
	}

	// Print Board.
	pGame->mainBoard->PrintBoard();
}

void Game::EndGame()
{
	// get singleton instance.
	Game* pGame = Game::privGetInstance();

	if (!pGame->playerExit)
	{
		pGame->CheckScore();
	}

	// Delete human player
	delete pGame->humanPlayer;

	// Delete ai player
	delete pGame->aiPlayer;

	// Destory Board.
	pGame->mainBoard->DestroyBoard();

	// delete main board.
	delete pGame->mainBoard;
}

void Game::PlayerExit()
{
	printf("\nPlayer Quit!\n");
	Game::privGetInstance()->playerExit = true;
}

Game* Game::privGetInstance()
{
	// singleton class instance.
	static Game instance;
	return &instance;
}
