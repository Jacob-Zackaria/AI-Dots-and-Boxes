#ifndef BOARD_H
#define BOARD_H

// header file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RETURN_IGNORE(x) (void(x))

struct Box
{
	enum class WonBy
	{
		HUMAN,
		AI,
		NONE
	};

	Box()
		:
		top(false), bottom(false),
		left(false), right(false),
		value(0), won(WonBy::NONE)
	{
	}

	const char WonByChar()
	{
		if (this->won == WonBy::NONE)
		{
			return '-';
		}
		else if(this->won == WonBy::HUMAN)
		{
			return 'H';
		}
		else
		{
			return 'A';
		}
	}

	bool top;
	bool bottom;
	bool left;
	bool right;
	unsigned int value;
	WonBy won;
};


class Board
{
public:
	
	// default constructor.
	Board();

	// deleted copy assignment operator.
	Board(const Board& newBoard);

	// deleted assignment operator.
	const Board& operator = (const Board&) = delete;

	// destructor.
	~Board();

	//------> Public functions <-----//
	
	// generate board.
	void GenerateBoard();

	// destroy board.
	void DestroyBoard();

	// print board.
	void PrintBoard(const bool useNumber = false);

	// check if all boxes are filled.
	bool IsFilled();

	// check if given box number is owned.
	bool CheckValidBox(const unsigned int boxNum);

	// check if given line is owned in the given box number.
	bool CheckValidLine(const unsigned int boxNum, const int lineNum);

	// assign line to the given box number.
	void AssignLine(const unsigned int boxNum, const int lineNum);

	// check if given boxnum is won.
	bool CheckBoxWon(const unsigned int boxNum);

	// check if neighbout box is won, which is checked by the given linenum.
	bool CheckNeighbourBoxWon(const unsigned int boxNum, const int lineNum, int& neighbourNum);

	// assign win to given boxnum.
	void AssignWin(const unsigned int boxNum, const bool humanWon);

	// get value of given boxnum.
	const unsigned int GetBoxVal(const unsigned int boxNum);

	// get total size (row * col)
	const unsigned int TotalSize() const;

	// get box pointer
	Box* GetBox() const;

	// get side string
	const char* GetSide(const int lineNum);

	// get human score
	unsigned int GetHumanScore() const;

	// get ai score
	unsigned int GetAIScore() const;

	//-------------------------------//

private:

	//------> Private functions <-----//

	// print column line
	void privPrintLine(const int i);

	// print column space
	void privPrintSpace(const int i);

	// print column char
	void privPrintChar(const int i, const bool useNumber);

	//-------------------------------//
	
	//------> Data <-----//
	 
	// board size.
	unsigned int size;

	// pointer to array of boxes
	Box* boxes;

	//-------------------//
};


#endif BOARD_H