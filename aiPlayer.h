#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "board.h"

class AIPlayer
{
	private:
		int side_;
		int ntiles_;
		std::default_random_engine rng_;
		std::uniform_int_distribution<int> rng_uniform_;
	
	public:
		AIPlayer (int s) : side_(s), ntiles_(s*s), rng_uniform_(0,s-1)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			rng_.seed(seed);
		}
		std::pair<int,int> nextMove(HexBoard board);
};
