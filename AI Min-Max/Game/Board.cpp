#include "Board.h"
#include<cstring>
Board::Board()
	:
	size(0),
	boxes(nullptr)
{

}

Board::Board(const Board& newBoard)
	:
	size(newBoard.size)
{
	// create a new location for box.
	this->boxes = new Box[this->size * this->size];

	// memory copy all the data from given board.
	memcpy(this->boxes, newBoard.boxes, sizeof(Box) * (static_cast<unsigned long long>(this->TotalSize())));
}

void Board::privPrintLine(const int i)
{
	printf("*");
	// column line
	for (unsigned int j = 0; j < this->size; j++)
	{
		if (this->boxes[(i * this->size) + j].bottom)
		{
			printf("-----");
		}
		else
		{
			printf(" . . ");
		}
		
		printf("*");
	}
	printf("\n");
}

void Board::privPrintSpace(const int i)
{
	// column space
	if (this->boxes[(i * this->size)].left)
	{
		printf("|");
	}
	else
	{
		printf(".");
	}
	// column space
	for (unsigned int j = 0; j < this->size; j++)
	{
		printf("     ");

		if (this->boxes[(i * this->size) + j].right)
		{
			printf("|");
		}
		else
		{
			printf(".");
		}
		
	}
	printf("\n");
}

void Board::privPrintChar(const int i, const bool useNumber)
{
	// column space
	if (this->boxes[(i * this->size)].left)
	{
		printf("|");
	}
	else
	{
		printf(".");
	}
	// column char
	for (unsigned int j = 0; j < this->size; j++)
	{
		char printC = this->boxes[(i * this->size) + j].WonByChar();
		if (useNumber && (printC == '-'))
		{
			printf("  %d  ", (i * this->size) + j + 1);
		}
		else
		{
			printf("  %c  ", printC);
		}
		
		// column space
		if (this->boxes[(i * this->size) + j].right)
		{
			printf("|");
		}
		else
		{
			printf(".");
		}
	}
	printf("\n");
}


Board::~Board()
{
}

void Board::GenerateBoard()
{
	// read the size of board.
	printf("\nSize of board: ");
	RETURN_IGNORE(scanf_s("%d", &this->size));

	// create size * size - array.
	this->boxes = new Box[this->size * this->size];

	// generate random based on time
	srand((unsigned int)time(NULL));

	for (unsigned int i = 0; i < this->TotalSize(); i++)
	{
		// random number between 1 and 5.
		this->boxes[i].value = (unsigned int)((rand() % 5) + 1);
	}
}

void Board::DestroyBoard()
{
	// destroy array.
	delete[] this->boxes;
}

void Board::PrintBoard(const bool useNumber)
{
	printf("\n");

	printf("*");
	// column line
	for (unsigned int j = 0; j < this->size; j++)
	{
		if (this->boxes[j].top)
		{
			printf("-----");
		}
		else
		{
			printf(" . . ");
		}

		printf("*");
	}
	printf("\n");
	// row
	for (unsigned int i = 0; i < this->size; i++)
	{
		this->privPrintSpace(i);

		this->privPrintChar(i, useNumber);

		this->privPrintSpace(i);

		this->privPrintLine(i);
	}
	
	printf("\n");
}

bool Board::IsFilled()
{
	// loop all boxes to check if everything is filled.
	for (unsigned int i = 0; i < this->TotalSize(); i++)
	{
		// if not filled return false.
		if (this->boxes[i].won == Box::WonBy::NONE)
		{
			return false;
		}
	}

	// return true, if all boxes are filled.
	return true;
}

bool Board::CheckValidBox(const unsigned int boxNum)
{
	if (boxNum < 1 || boxNum > this->TotalSize())
	{
		printf("\nWrong Input!");
		return false;
	}

	if (this->boxes[boxNum - 1].WonByChar() == '-')
	{
		// box available.
		return true;
	}

	
	return false;
}

bool Board::CheckValidLine(const unsigned int boxNum, const int lineNum)
{
	if (lineNum < 1 || lineNum > 4)
	{
		printf("\nWrong Input!");
		return false;
	}

	bool status = true;
	switch (lineNum)
	{
		// left check
	case 1:
		if (this->boxes[boxNum - 1].left)
		{
			status = false;
		}
		break;
		// right check
	case 2:
		if (this->boxes[boxNum - 1].right)
		{
			status = false;
		}
		break;
		// up check
	case 3:
		if (this->boxes[boxNum - 1].top)
		{
			status = false;
		}
		break;
		// down check
	case 4:
		if (this->boxes[boxNum - 1].bottom)
		{
			status = false;
		}
		break;
	default:
		printf("\nWrong Input!");
		return false;
	}

	return status;
}

void Board::AssignLine(const unsigned int boxNum, const int lineNum)
{
	switch (lineNum)
	{
	case 1:
		// assign left line to the box.
		this->boxes[boxNum - 1].left = true;
		if ((boxNum - 1) % this->size != 0)
		{
			// also assign right line of left box.
			this->boxes[boxNum - 2].right = true;
		}
		break;
	case 2:
		// assign right line to the box.
		this->boxes[boxNum - 1].right = true;
		if ((boxNum) % this->size != 0)
		{
			// also assign left line of right box.
			this->boxes[boxNum].left = true;
		}
		break;
	case 3:
		// assign top line to the box.
		this->boxes[boxNum - 1].top = true;
		if ((boxNum) > this->size)
		{
			// also assign bottom line of top box.
			this->boxes[(boxNum - 1) - this->size].bottom = true;
		}
		break;
	case 4:
		// assign bottom line to the box.
		this->boxes[boxNum - 1].bottom = true;
		if ((boxNum - 1) < (this->TotalSize() - this->size))
		{
			// also assign top line of bottom box.
			this->boxes[(boxNum - 1) + this->size].top = true;
		}
		break;
	default:
		break;
	}
}

bool Board::CheckBoxWon(const unsigned int boxNum)
{
	bool status = true;
	if (!this->boxes[boxNum - 1].top)
	{
		status = false;
	}
	else if(!this->boxes[boxNum - 1].bottom)
	{
		status = false;
	}
	else if (!this->boxes[boxNum - 1].left)
	{
		status = false;
	}
	else if (!this->boxes[boxNum - 1].right)
	{
		status = false;
	}

	return status;
}

bool Board::CheckNeighbourBoxWon(const unsigned int boxNum, const int lineNum, int& neighbourNum)
{
	bool status = false;
	switch (lineNum)
	{
	case 1:
		// check left box
		if ((boxNum - 1) % this->size != 0)
		{
			neighbourNum = boxNum - 1;
			status = this->CheckBoxWon(neighbourNum);
		}
		break;
	case 2:
		// check right box
		if ((boxNum) % this->size != 0)
		{
			neighbourNum = boxNum + 1;
			status = this->CheckBoxWon(neighbourNum);
		}
		break;
	case 3:
		// check up box
		if ((boxNum) > this->size)
		{
			neighbourNum = boxNum - this->size;
			status = this->CheckBoxWon(neighbourNum);
		}
		break;
	case 4:
		// check down box
		if ((boxNum - 1) < (this->TotalSize() - this->size))
		{
			neighbourNum = boxNum + this->size;
			status = this->CheckBoxWon(neighbourNum);
		}
		break;
	default:
		break;
	}

	return status;
}

void Board::AssignWin(const unsigned int boxNum, const bool humanWon)
{
	if (humanWon)
	{
		this->boxes[boxNum - 1].won = Box::WonBy::HUMAN;
	}
	else
	{
		this->boxes[boxNum - 1].won = Box::WonBy::AI;
	}
}

const unsigned int Board::GetBoxVal(const unsigned int boxNum)
{
	return this->boxes[boxNum - 1].value;
}

const unsigned int Board::TotalSize() const
{
	return (this->size * this->size);
}

Box* Board::GetBox() const
{
	return this->boxes;
}

const char* Board::GetSide(const int lineNum)
{
	switch (lineNum)
	{
	case 1:
		return "LEFT";
	case 2:
		return "RIGHT";
	case 3:
		return "TOP";
	case 4:
		return "BOTTOM";
	default:
		return "NONE";
	}
}

unsigned int Board::GetHumanScore() const
{
	unsigned int score = 0;
	for (unsigned int i = 0; i < this->TotalSize(); i++)
	{
		if (this->boxes[i].WonByChar() == 'H')
		{
			score += this->boxes[i].value;
		}
	}

	return score;
}

unsigned int Board::GetAIScore() const
{
	unsigned int score = 0;
	for (unsigned int i = 0; i < this->TotalSize(); i++)
	{
		if (this->boxes[i].WonByChar() == 'A')
		{
			score += this->boxes[i].value;
		}
	}

	return score;
}
