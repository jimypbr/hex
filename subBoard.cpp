//
// Created by James on 15/09/15.
//

#include <vector>
#include "board.h"
#include "subBoard.h"

SubHexBoard getEmptySubHexBoard(const HexBoard& board)
{
    // count # of empty tiles
    int n_empty = 0;
    for (int tile = 0; tile < board.ntiles(); ++tile)
    {
        if (board[tile] == TileColour::EMPTY)
        {
            n_empty++;
        }
    }

    std::vector<int> coords(n_empty);
    std::vector<TileColour> colours(n_empty, TileColour::EMPTY);

    // coords of emtpy tiles
    int side = board.side();
    int k=0;
    for (int i=0; i<side; i++)
    {
        for (int j=0; j<side; j++)
        {
            const int addr = i*side+j;
            if (board[addr] == TileColour::EMPTY)
            {
                coords[k] = addr;
                k++;
            }
        }
    }

    // pack both vectors into EmptyTiles struct and copy out
    SubHexBoard sb;
    sb.coords = std::move(coords);
    sb.colours = std::move(colours);

    return sb;
}

void insertSubHexBoard(const SubHexBoard& sub_board, HexBoard& board)
{
    // gather subboard into board
    int size = sub_board.colours.size();

    for (int i = 0; i < size; ++i)
    {
        const int addr = sub_board.coords[i];
        board[addr] =  sub_board.colours[i];
    }
}

