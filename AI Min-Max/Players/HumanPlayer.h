#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:
	// default constructor.
	HumanPlayer();

	// deleted copy assignment operator.
	HumanPlayer(const HumanPlayer&) = delete;

	// deleted assignment operator.
	const HumanPlayer& operator = (const HumanPlayer&) = delete;

	// destructor.
	virtual ~HumanPlayer();

	// override base update
	virtual void Update(Board& mainBoard) override;

private:

	// read input
	const bool GetInput(Board& mainBoard, int& boxNum);

	// execute move
	void Execute(Board& mainBoard, const int boxNum);
};


#endif HUMAN_H