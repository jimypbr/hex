#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"

struct EmptyTiles
{
	std::vector<int> coords;
	std::vector<TileColour> sub_board;
};

class AIPlayer
{
public:
	AIPlayer() {}
	virtual std::pair<int,int> nextMove(HexBoard board, const HexGraph& hex_graph) const = 0;
};

