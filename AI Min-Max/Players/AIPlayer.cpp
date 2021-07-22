#include "AIPlayer.h"
#include "Board.h"
#include "SearchSpace.h"

AIPlayer::AIPlayer()
{
}

AIPlayer::~AIPlayer()
{
}

// override base class function
void AIPlayer::Update(Board& mainBoard)
{
	printf("\nAI >\n");

	// generate moves for ai to take from main board.
	if (SearchSpace::GenerateMoves(mainBoard))
	{
		// search genearated children for move
		SearchSpace::SearchChildrenForMove();

		// start move.
		SearchSpace::Execute(mainBoard);
	}

	// destory generated moves.
	SearchSpace::DestroyMoves();
}
