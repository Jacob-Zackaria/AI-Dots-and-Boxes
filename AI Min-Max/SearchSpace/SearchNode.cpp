#include "SearchNode.h"

SearchNode::SearchNode(const Board& newBoard)
	:
	pParent(nullptr),
	pChild{},
	currentBoard(new Board(newBoard)),
	pData(new SearchNodeData())
{
}

SearchNode::SearchNode(Board* newBoard, SearchNode* newParent, SearchNodeData* newData)
	:
	pParent(newParent),
	pChild{},
	currentBoard(newBoard),
	pData(newData)
{
}


SearchNode::~SearchNode()
{
	// destroy current board.
	this->currentBoard->DestroyBoard();

	// destroy node data.
	delete this->pData;
}

const unsigned int SearchNode::GetDepth() const
{
	return this->pData->GetCurrentDepth();
}

void SearchNode::GenerateChildren()
{
	// find new state { if max, get min and vice versa }
	SearchNodeData::MinMax newState = (SearchNodeData::MinMax)(((unsigned int)this->pData->GetCurrentState() + 1) % 2);

	// iterate through all boxes.
	for (unsigned int i = 0; i < this->currentBoard->TotalSize(); i++)
	{
		// box number
		const int boxNum = i + 1;

		// check if it is a valid box
		if (this->currentBoard->CheckValidBox(boxNum))
		{
			// check all lines in the box { same options as human. 1:LEFT, 2:RIGHT, 3:UP, 4:DOWN }
			for (int j = 1; j < 5; j++)
			{
				if (this->currentBoard->CheckValidLine(boxNum, j))
				{
					// create new child board and assign line.
					Board* newBoard = new Board(*this->currentBoard);
					newBoard->AssignLine(boxNum, j);

					// check if box won.
					if (newBoard->CheckBoxWon(boxNum))
					{
						// if won, assign won state as ai.
						newBoard->AssignWin(boxNum, false);
					}

					// assign child node data.
					SearchNodeData* newData = new SearchNodeData(newState, this->pData->GetCurrentDepth() + 1, nullptr,
						boxNum, j);

					// generate a new child node.
					SearchNode* newChild = new SearchNode(newBoard, this, newData);

					// add to child node list.
					this->pChild.push_back(newChild);
				}
			}
		}
	}
}

SearchNode* SearchNode::GetChild(unsigned int index) const
{
	if (this->pChild.size() == 0)
	{
		return nullptr;
	}
	else if (index > (this->pChild.size() - 1))
	{
		return nullptr;
	}
	else
	{
		return this->pChild.at(index);
	}
}

SearchNode* SearchNode::GetParent() const
{
	return this->pParent;
}

SearchNodeData* SearchNode::GetData() const
{
	return this->pData;
}

Board* SearchNode::GetBoard() const
{
	return this->currentBoard;
}
