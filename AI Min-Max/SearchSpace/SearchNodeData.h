#ifndef SEARCH_NODE_DATA_H
#define SEARCH_NODE_DATA_H


class SearchNodeData
{
public:

	enum class MinMax
	{
		MIN,
		MAX
	};

	// default constructor.
	SearchNodeData();

	// specialized constructor.
	SearchNodeData(const MinMax newState, unsigned int newDepth, int* newScore, unsigned int boxNum, unsigned int lineNum);

	// deleted copy assignment operator.
	SearchNodeData(const SearchNodeData&) = delete;

	// deleted assignment operator.
	const SearchNodeData& operator = (const SearchNodeData&) = delete;

	// destructor.
	~SearchNodeData();

	//------> Public functions <-----//

	// get current state
	const MinMax GetCurrentState() const;

	// get depth
	const unsigned int GetCurrentDepth() const;

	// get score pointer
	const int* GetCurrentScore() const;

	// get box number
	const unsigned int GetCurrentBoxNum() const;

	// get line number
	const unsigned int GetCurrentLineNum() const;

	// set current score.
	void SetCurrentScore(const int newScore);

	//-------------------------------//

private:

	//------> Data <-----//

	// Min-Max
	MinMax currentState;

	// depth
	unsigned int depth;

	// score.
	int* currentScore;

	// box number
	unsigned int currentBoxNum;

	// line number
	unsigned int currentLineNum;
	

	//-------------------//
};

#endif SEARCH_NODE_DATA_H