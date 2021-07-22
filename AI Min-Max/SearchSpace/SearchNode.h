#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include "SearchNodeData.h"
#include "Board.h"
#include<vector>

class SearchNode
{
public:

	// default constructor.
	SearchNode() = delete;

	// specialized constructor
	SearchNode(const Board& newBoard);

	// specialized constructor
	SearchNode(Board* newBoard, SearchNode* newParent, SearchNodeData* newData);

	// deleted copy assignment operator.
	SearchNode(const SearchNode&) = delete;

	// deleted assignment operator.
	const SearchNode& operator = (const SearchNode&) = delete;

	// destructor.
	~SearchNode();

	//------> Public functions <-----//

	// get depth of search node.
	const unsigned int GetDepth() const;

	// generate children for current node.
	void GenerateChildren();

	// get child based on index.
	SearchNode* GetChild(unsigned int index) const;

	// get parent
	SearchNode* GetParent() const;

	// get data of search node
	SearchNodeData* GetData() const;

	// get current board
	Board* GetBoard() const;

	//-------------------------------//

private:

	//------> Private functions <-----//

	

	//-------------------------------//

	//------> Data <-----//
	
	// parent link.
	SearchNode* pParent;

	// child links.
	std::vector<SearchNode*> pChild;

	// current board
	Board* currentBoard;

	// data of node.
	SearchNodeData* pData;
	
	//-------------------//
};

#endif SEARCH_NODE_H