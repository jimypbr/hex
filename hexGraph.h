#pragma once

#include <vector>
#include "board.h"

class HexGraph
{
	private:
		int board_side_;

	public:
		HexGraph (int s) : board_side_(s) {}
		bool whiteWon (const HexBoard& board) const;
		bool blackWon (const HexBoard& board) const;
};
