#pragma once

#include <vector>

enum class TileColour {EMPTY, WHITE, BLACK};

/**
 * Return given a tile colour, return its opposite.
 * The opposite of EMPTY is EMPTY.
 */
inline TileColour oppositeColour(TileColour c)
{
    TileColour opposite;
    switch(c)
    {
        case TileColour::BLACK:
            opposite = TileColour::WHITE;
            break;
        case TileColour :: WHITE:
            opposite = TileColour::BLACK;
            break;
        default:
            opposite = TileColour::EMPTY;
            break;
    }
    return opposite;
}

/**
 * The Hex game board.
 * Contains the board dimensions and the TileColour (EMPTY / WHITE / BLACK) of
 * every tile in the board.
 */
class Board
{
private:
    /**
     * The number of tiles on the side of the board
     */
    int side_;

    /**
     * Total number of tiles: side*side
     */
    int ntiles_;

    /**
     * Board represented as a flattened 2d vector of TileColours
     */
    std::vector<TileColour> board_;

public:
    /**
     * Constructor
     * @param s Board side length
     */
    Board(int s): side_(s), ntiles_(s*s), board_(s*s, TileColour::EMPTY) {}

    /**
     * @return number of tiles on side of board
     */
    int side() const
    {
        return side_;
    }

    /**
     * @return number of tiles in board.
     */
    int ntiles() const
    {
        return ntiles_;
    }

    /**
     * Overload subscript operator to get/set individual tiles
     */
    TileColour& operator[](int idx)
    {
        return board_[idx];
    }

    TileColour& operator() (unsigned row, unsigned col)
    {
        int idx = (row-1) * side_ + (col-1);
        return board_[idx];
    }
    const TileColour& operator[](int idx) const
    {
        return board_[idx];
    }
};

