//
// Created by James Briggs on 15/09/15.
//

#ifndef HEX_SUBBOARD_H
#define HEX_SUBBOARD_H

#include <vector>
#include "board.h"

/**
 * Data structure representing a subset of the tile positions of
 * a hex board and the colour of the piece at each of those positions.
 */
struct SubHexBoard
{
    // 1d coordinates of the empty tiles
    std::vector<int> coords;

    // tile colours of the sub_board
    std::vector<TileColour> colours;
};

/**
 * Insert the pieces and corresponding tiles of a sub-board
 *
 * @param sub_board A sub-board of tiles with colours to be inserted into the HexBoard
 * @return board The hex board updated with the positions from the sub-board.
 */
void insertSubHexBoard(const SubHexBoard& sub_board, HexBoard& board);

/**
 * Create a sub-board from all the empty positions from a hex board.
 *
 * @param board A hex board
 * @return A sub-board of the empty positions in board.
 */
SubHexBoard getEmptySubHexBoard(const HexBoard& board);

#endif //HEX_SUBBOARD_H