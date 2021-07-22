#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

class AIPlayer : public Player
{
public:
	// default constructor.
	AIPlayer();

	// deleted copy assignment operator.
	AIPlayer(const AIPlayer&) = delete;

	// deleted assignment operator.
	const AIPlayer& operator = (const AIPlayer&) = delete;

	// destructor.
	virtual ~AIPlayer();

	// override base class function
	virtual void Update(Board& mainBoard) override;
};


#endif AI_PLAYER_H