#pragma once

#include <vector>

enum class TileColour {EMPTY, WHITE, BLACK};

/*
 * The Hex game board.
 * Contains the board dimensions and the TileColour (EMPTY / WHITE / BLACK) of
 * every tile in the board.
 */
class HexBoard
{
private:
    /*
     * Board represented as a flattened 2d vector of TileColours
     */
    std::vector<TileColour> board_;

    /*
     * The number of tiles on the side of the board
     */
    int side_;

    /*
     * Total number of tiles: side*side
     */
    int ntiles_;

public:
    HexBoard(int s): side_(s), ntiles_(s*s), board_(s*s, TileColour::EMPTY) {}

    /*
     * Get number of tiles on side of board
     */
    int side() const
    {
        return side_;
    }

    /*
     * Get number of tiles in board.
     */
    int ntiles() const
    {
        return ntiles_;
    }

    /*
     * Overload subscript operator to get/set individual tiles
     */
    TileColour& operator[](int idx)
    {
        return board_[idx];
    }
    const TileColour& operator[](int idx) const
    {
        return board_[idx];
    }
};

