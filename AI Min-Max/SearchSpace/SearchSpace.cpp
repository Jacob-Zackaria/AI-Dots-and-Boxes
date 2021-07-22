#include "SearchSpace.h"
#include "DepthFirstSearch.h"
#include "Game.h"

SearchSpace::SearchSpace()
	:
	rootNode(nullptr),
	ply(0)
{
}

void SearchSpace::privParentScore(SearchNode* rootNode)
{
	// get parent node of current root node
	SearchNode* parentNode = rootNode->GetParent();
	if (parentNode != nullptr)
	{
		// get score from root node
		int currScore = *rootNode->GetData()->GetCurrentScore();

		// if score is null
		if (parentNode->GetData()->GetCurrentScore() != nullptr)
		{
			// get parentScore
			int pScore = *parentNode->GetData()->GetCurrentScore();

			// check if parent node is min state
			if (parentNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MIN && (currScore < pScore))
			{
				parentNode->GetData()->SetCurrentScore(currScore);
			} // else check if parent node is max state
			else if (parentNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MAX && (currScore > pScore))
			{
				parentNode->GetData()->SetCurrentScore(currScore);
			}
		}
		else
		{
			// set current score as rootNode score
			parentNode->GetData()->SetCurrentScore(currScore);
		}
	}
}

void SearchSpace::privChildScore(SearchNode* rootNode, SearchNode* childNode)
{
	// compare with child score.
	int rootSCore = *rootNode->GetData()->GetCurrentScore();
	int childNodeScore = *childNode->GetData()->GetCurrentScore();

	if (rootNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MIN && (childNodeScore < rootSCore))
	{
		rootNode->GetData()->SetCurrentScore(childNodeScore);
	}
	else if (rootNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MAX && (childNodeScore > rootSCore))
	{
		rootNode->GetData()->SetCurrentScore(childNodeScore);
	}
}

bool SearchSpace::pruneSearch(SearchNode* rootNode)
{
	// get parent node
	SearchNode* parentNode = rootNode->GetParent();
	if (parentNode != nullptr)
	{
		// check if score of parent and root is available.
		const int* parentScore = parentNode->GetData()->GetCurrentScore();
		const int* currentScore = rootNode->GetData()->GetCurrentScore();
		if (parentScore != nullptr && currentScore != nullptr)
		{
			// check if parent node is max and compare score.
			if (parentNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MAX && (*currentScore < *parentScore))
			{
				// prune search for child.
				return true;
			} // else check if parent node is min and compare score.
			else if (parentNode->GetData()->GetCurrentState() == SearchNodeData::MinMax::MIN && (*currentScore > *parentScore))
			{
				// prune search for child.
				return true;
			}
		}
	}

	return false;
}

void SearchSpace::privSearchChildren(SearchNode* rootNode)
{
	// get child list
	unsigned int index = 0;
	SearchNode* childNode = rootNode->GetChild(index);

	// iterate through all child node.
	while (childNode != nullptr)
	{
		// check for pruning
		if (this->pruneSearch(rootNode))
		{
			// if pruned, do not expand children
			break;
		}

		// expand its children node
		SearchSpace::privGetInstance()->privSearchChildren(childNode);

		// calculate score.
		if (rootNode->GetData()->GetCurrentScore() == nullptr)
		{
			// set score for current root node from child, if still empty
			rootNode->GetData()->SetCurrentScore(*childNode->GetData()->GetCurrentScore());
		}
		else
		{
			// calculate with child score
			this->privChildScore(rootNode, childNode);
		}

		// get next child
		index++;
		childNode = rootNode->GetChild(index);
	}

	// if leaf, find score  using given method.
	if (rootNode->GetChild(0) == nullptr)
	{
		// get ai score from current board
		int aiScore = rootNode->GetBoard()->GetAIScore();

		// get human score from current board
		int humanScore = rootNode->GetBoard()->GetHumanScore();

		// setting value for leaf node, using human score - ai score. 
		rootNode->GetData()->SetCurrentScore(humanScore - aiScore);
	}

	// Check parent node
	this->privParentScore(rootNode);
}


SearchSpace::~SearchSpace()
{
}

void SearchSpace::SetSettings()
{
	// get singleton instance.
	SearchSpace* pSpace = SearchSpace::privGetInstance();

	while (pSpace->ply < 1)
	{
		// read the depth.
		printf("\nAI Search ply: ");
		RETURN_IGNORE(scanf_s("%d", &pSpace->ply));

		if (pSpace->ply < 0)
		{
			// if value less than 1
			printf("\nInput number greater than 0\n");
		}
	}
}

bool SearchSpace::GenerateMoves(const Board& mainBoard)
{
	// get singleton instance.
	SearchSpace* pSpace = SearchSpace::privGetInstance();

	// create the root search node.
	pSpace->rootNode = new SearchNode(mainBoard);

	// do the depth first search to generate childrens.
	bool success = DepthFirstSearch(*pSpace->rootNode, pSpace->ply);
	if (!success)
	{
		printf("\n\n ALGORITHM EXCEEDED MAX TIME  5 Min!\n");

		// ai exit
		Game::PlayerExit();
	}

	return success;
}

void SearchSpace::SearchChildrenForMove()
{
	// get singleton instance.
	SearchSpace* pSpace = SearchSpace::privGetInstance();

	// private search
	pSpace->privSearchChildren(pSpace->rootNode);

}

void SearchSpace::Execute(Board& mainBoard)
{
	// get singleton instance.
	SearchSpace* pSpace = SearchSpace::privGetInstance();

	// get root score
	int rootScore = *pSpace->rootNode->GetData()->GetCurrentScore();

	// get child list
	unsigned int index = 0;
	SearchNode* childNode = pSpace->rootNode->GetChild(index);

	// iterate through all child node.
	while (childNode != nullptr)
	{
		// check if root score is equal to child score.
		if (rootScore == *childNode->GetData()->GetCurrentScore())
		{
			// if equal, assign line as that of child.
			mainBoard.AssignLine(childNode->GetData()->GetCurrentBoxNum(), childNode->GetData()->GetCurrentLineNum());

			printf("\nLine drawn on Box : %d, Side : %s", childNode->GetData()->GetCurrentBoxNum(), mainBoard.GetSide(childNode->GetData()->GetCurrentLineNum()));

			// check if ai won the box
			if (mainBoard.CheckBoxWon(childNode->GetData()->GetCurrentBoxNum()))
			{
				// if won, assign won state as ai
				mainBoard.AssignWin(childNode->GetData()->GetCurrentBoxNum(), false);

				printf("\nBox : %d won by ai!", childNode->GetData()->GetCurrentBoxNum());
			}

			// check if neighbour box won
			int neighbourNum = 0;
			if (mainBoard.CheckNeighbourBoxWon(childNode->GetData()->GetCurrentBoxNum(), childNode->GetData()->GetCurrentLineNum(), neighbourNum))
			{
				// if won, assign won state as ai
				mainBoard.AssignWin(neighbourNum, false);

				printf("\nNeighbour Box : %d won by ai!", neighbourNum);
			}

			// exit loop
			break;
		}

		// get next child
		index++;
		childNode = pSpace->rootNode->GetChild(index);
	}
}

void SearchSpace::DestroyMoves()
{
	// delete root node.
	delete  SearchSpace::privGetInstance()->rootNode;
}

SearchSpace* SearchSpace::privGetInstance()
{
	// singleton class instance.
	static SearchSpace instance;
	return &instance;
}
