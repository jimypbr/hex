
#include <utility>		// std::pair
#include <random>
#include <functional> 	// std::bind
#include "board.h"
#include "aiPlayer.h"

std::pair<int,int> AIPlayer :: nextMove (HexBoard board)
{
	auto coord_gen = std::bind ( rng_uniform_, rng_ );

	// generate random coord
	int row, col;
	for (;;)
	{
		row = coord_gen();
		col = coord_gen();

		if (board[row*side_ + col] == TileColour::EMPTY)
		{
			break;
		}
	}

	std::pair<int,int> coord = {row, col};
	return coord;
}
