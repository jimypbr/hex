#pragma once

#include <vector>
#include "board.h"

class HexGraph
{
	private:
		int size_;
		int board_side_;
	public:
		HexGraph (int s) : board_side_(s), size_(s*s) {}
		bool whiteWon (const HexBoard& board) const;
		bool blackWon (const HexBoard& board) const;
};
