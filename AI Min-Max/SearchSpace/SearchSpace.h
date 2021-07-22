#ifndef SEARCH_SPACE_H
#define SEARCH_SPACE_H

#include "SearchNode.h"

class SearchSpace
{
public:

	// deleted copy assignment operator.
	SearchSpace(const SearchSpace&) = delete;

	// deleted assignment operator.
	const SearchSpace& operator = (const SearchSpace&) = delete;

	// destructor.
	~SearchSpace();

	//------> Public functions <-----//

	// set search settings.
	static void SetSettings();

	// generate moves.
	static bool GenerateMoves(const Board& mainBoard);

	// search generated choldren for move
	static void SearchChildrenForMove();

	// start move
	static void Execute(Board& mainBoard);

	// destroy search space.
	static void DestroyMoves();

	//-------------------------------//

private:

	//------> Private functions <-----//

	// singleton class instance.
	static SearchSpace* privGetInstance();

	// private default constructor.
	SearchSpace();

	// search generated choldren for move
	void privSearchChildren(SearchNode* rootNode);

	// assign parent score
	void privParentScore(SearchNode* rootNode);

	// assign child score
	void privChildScore(SearchNode* rootNode, SearchNode* childNode);

	// prune search space
	bool pruneSearch(SearchNode* rootNode);

	//-------------------------------//

	//------> Data <-----//

	// root node.
	SearchNode* rootNode;

	// depth to search
	unsigned int ply;

	//-------------------//
};

#endif SEARCH_SPACE_H