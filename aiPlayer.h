#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"

/**
 * Abstract class for AI Hex player.
 */
class AIPlayer
{
public:
	/**
	 * Given a HexBoard, decide which move to make next.
	 *
	 * @param board A game board in some state of play
	 * @return A pair of ints representing the coordinates (x,y) of AIs next move.
	 */
	virtual std::pair<int,int> nextMove(HexBoard board) const = 0;
};

