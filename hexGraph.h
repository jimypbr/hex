#pragma once

#include <vector>
#include "board.h"

class HexGraph
{
private:
	/* Given a board tile index t, return vector
	 * of board tile indices of s's neighbours. */
	std::vector<int> neighbourNodes_(int t, int side) const;

public:
	HexGraph() {}
	bool whiteWon(const HexBoard& board) const;
	bool blackWon(const HexBoard& board) const;

	/* Find winner in case where board has no empty tiles */
	TileColour fullBoardWinner(const HexBoard& board) const;
};
