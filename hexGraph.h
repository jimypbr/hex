#pragma once

#include <vector>
#include "board.h"

namespace HexGraph
{
	/**
	 * Get the neighbours of a board tile.
	 *
	 * @param t board tile index
	 * @param side board side length
	 * @return vector of board tile indices of t's neighbours.
	 * */
	std::vector<int> neighbourNodes(int t, int side);

	void neighbourNodesFast(int t, int side, std::vector<int> &neighbours);

	/**
	 * Has white won?
	 *
	 * @param board A hex board to be evaluated
	 * @return bool true if white has won; else false
	 */
	bool whiteWon(const Board& board);

	/**
	 * Has black won?
	 *
	 * @param board A hex board to be evaluated
	 * @return bool true if black has won; else false
	 */
	bool blackWon(const Board& board);

	/**
	 * Calculate the winning colour in the specialised case
	 * where board has no empty tiles.
	 *
	 * @param board A hex board where all the tiles are filled
	 * @return The colour of the winning player.
	 */
	TileColour fullBoardWinner(const Board& board);
};
