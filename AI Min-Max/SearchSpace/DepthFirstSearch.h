#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#define MAX_ALGORITHM_TIME 300000   // (5 * 60 * 1000)

#include "SearchNode.h"
#include<queue>
#include <chrono>

bool DepthFirstSearch(SearchNode& newNode, unsigned int ply)
{
	// queue.
	std::deque<SearchNode*> currentQueue = {};

	// add root node to queue.
	currentQueue.push_back(&newNode);

	// get current time
	auto startTime = std::chrono::steady_clock::now();

	while (!currentQueue.empty())
	{
		// get current time
		auto timePoint = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - startTime).count() > MAX_ALGORITHM_TIME)
		{
			// unsuccessfull
			return (false);
		}
		
		// get last node.
		SearchNode* removedNode = currentQueue.back();

		// remove last node from queue
		currentQueue.pop_back();

		// check if ply is reached.
		if (removedNode->GetDepth() < ply)
		{
			// if not, generate all children for current board.
			removedNode->GenerateChildren();

			// get child list
			unsigned int index = 0;
			SearchNode* childNode = removedNode->GetChild(index);

			while (childNode != nullptr)
			{
				// add to queue
				currentQueue.push_back(childNode);

				// get next child
				index++;
				childNode = removedNode->GetChild(index);
			}
		}

	}

	// success
	return true;
}

#endif DEPTH_FIRST_SEARCH_H