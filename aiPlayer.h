#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"

struct EmptyTiles
{
	std::vector<int> coords;
	HexBoard sub_board;
};

class AIPlayer
{
	private:
		int side_;
		int ntiles_;
		std::uniform_int_distribution<int> rng_uniform_;
		std::default_random_engine rng_;
		double monteCarloScore_(HexBoard &board, const HexGraph &hex_graph, const int niter) const;
		void insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const;
		EmptyTiles getEmptyTiles_(const HexBoard& board) const;
		std::pair<int,int> randomMove_(HexBoard& board) const;
	
	public:
		AIPlayer (int s) : side_(s), ntiles_(s*s), rng_uniform_(0,s-1)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			rng_.seed(seed);
		}
		std::pair<int,int> nextMove(HexBoard board, const HexGraph& hex_graph) const;
};

