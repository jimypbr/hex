#pragma once

#include <vector>
#include "board.h"

namespace HexGraph
{
	/* Given a board tile index t, return vector
	 * of board tile indices of s's neighbours. */
	std::vector<int> neighbourNodes(int t, int side);
	bool whiteWon(const HexBoard& board);
	bool blackWon(const HexBoard& board);

	/* Find winner in case where board has no empty tiles */
	TileColour fullBoardWinner(const HexBoard& board);
};
