#ifndef PLAYER_H
#define PLAYER_H

class Board;

class Player
{
public:
	// default constructor.
	Player()
	{}

	// deleted copy assignment operator.
	Player(const Player&) = delete;

	// deleted assignment operator.
	const Player& operator = (const Player&) = delete;

	// destructor.
	virtual ~Player()
	{}

	// pure virtual function, inherited classes must implement.
	virtual void Update(Board& mainBoard) = 0;
};

#endif PLAYER_H