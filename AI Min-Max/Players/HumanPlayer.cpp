#include "HumanPlayer.h"
#include "Board.h"
#include "Game.h"

HumanPlayer::HumanPlayer()
{
}

HumanPlayer::~HumanPlayer()
{
}


// override base class function
void HumanPlayer::Update(Board& mainBoard)
{
	printf("\nHUMAN >\n");

	// print box with numbers
	mainBoard.PrintBoard(true);

	// read the input.
	int boxNum = 0;
	if (this->GetInput(mainBoard, boxNum))
	{
		// start move
		this->Execute(mainBoard, boxNum);
	}
}

// read input
const bool HumanPlayer::GetInput(Board& mainBoard, int& boxNum)
{
	while (true)
	{
		printf("\nEnter the box number to play: [or] '0' to exit: \n");
		RETURN_IGNORE(scanf_s("%d", &boxNum));

		if (boxNum == 0)
		{
			// if input is key 'E', exit game.
			Game::PlayerExit();
			return false;
		}

		if (mainBoard.CheckValidBox(boxNum))
		{
			break;
		}

		printf("\nBox already filled!");
	}

	return true;
}

// execute move
void HumanPlayer::Execute(Board& mainBoard, const int boxNum)
{
	int lineNum = 0;
	while (true)
	{
		printf("\nEnter the line number:\n");
		printf("1. LEFT  2. RIGHT  3.UP  4.DOWN\n");
		RETURN_IGNORE(scanf_s("%d", &lineNum));

		if (mainBoard.CheckValidLine(boxNum, lineNum))
		{
			break;
		}

		printf("\nLine already drawn!");
	}
	
	// assign line to the box.
	mainBoard.AssignLine(boxNum, lineNum);

	printf("\nLine drawn on Box : %d, Side : %s", boxNum, mainBoard.GetSide(lineNum));

	// check if human won the box
	if (mainBoard.CheckBoxWon(boxNum))
	{
		// if won, assign won state as human
		mainBoard.AssignWin(boxNum, true);

		printf("\nBox : %d won by human!", boxNum);
	}

	// check if neighbour box won
	int neighbourNum = 0;
	if (mainBoard.CheckNeighbourBoxWon(boxNum, lineNum, neighbourNum))
	{
		// if won, assign won state as human
		mainBoard.AssignWin(neighbourNum, true);

		printf("\nNeighbour Box : %d won by human!", neighbourNum);
	}
}
