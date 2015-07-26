#pragma once

#include <vector>
#include "board.h"

class HexGraph
{
	public:
		HexGraph() {}
		bool whiteWon(const HexBoard& board) const;
		bool blackWon(const HexBoard& board) const;

		/* Find winner in case where board has no empty tiles */
		TileColour fullBoardWinner(const HexBoard& board) const;
};
