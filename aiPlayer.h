#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"

class AIPlayer
{
	protected:
		int side_;
		int ntiles_;

	public:
		AIPlayer(int s) : side_(s), ntiles_(s*s) {}
		virtual std::pair<int,int> nextMove(HexBoard board, const HexGraph& hex_graph) const = 0;
};

