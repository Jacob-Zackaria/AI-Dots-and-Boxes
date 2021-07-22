#include "SearchNodeData.h"

SearchNodeData::SearchNodeData()
	:
	currentState(MinMax::MAX),
	depth(1),
	currentScore(nullptr),
	currentBoxNum(0),
	currentLineNum(0)
{
}

SearchNodeData::SearchNodeData(const MinMax newState, unsigned int newDepth, int* newScore, unsigned int boxNum, unsigned int lineNum)
	:
	currentState(newState),
	depth(newDepth),
	currentScore(newScore),
	currentBoxNum(boxNum),
	currentLineNum(lineNum)
{
}

SearchNodeData::~SearchNodeData()
{
}

const SearchNodeData::MinMax SearchNodeData::GetCurrentState() const
{
	return this->currentState;
}

const unsigned int SearchNodeData::GetCurrentDepth() const
{
	return this->depth;
}

const int* SearchNodeData::GetCurrentScore() const
{
	return this->currentScore;
}

const unsigned int SearchNodeData::GetCurrentBoxNum() const
{
	return this->currentBoxNum;
}

const unsigned int SearchNodeData::GetCurrentLineNum() const
{
	return this->currentLineNum;
}

void SearchNodeData::SetCurrentScore(const int newScore)
{
	this->currentScore = new int(newScore);
}
