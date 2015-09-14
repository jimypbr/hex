#pragma once

#include <memory>
#include <algorithm>    // std::count
#include "board.h"


/**
 * Node in Monte Carlo search tree that represents
 * a possible board configuration.
*/
struct MCNode
{
    int nWhiteWins = 0;
    int nBlackWins = 0;
    int nVisits = 0;
    int nEmpty;
    int move;

    HexBoard game;
    TileColour colour;

    std::vector<std::unique_ptr<MCNode>> children;

    MCNode(HexBoard game, TileColour col) : game(game), colour(col)
    {}

    /**
     * return true if node is leaf; else false
     */
    bool isLeaf()
    {
        return children.size() == 0;
    }

    /**
     * Update the stats of this node given a winning colour of a game
     */
    void updateStats(TileColour winner)
    {
        nVisits += 1;

        if (winner == TileColour::WHITE)
            nWhiteWins += 1;
        else
            nBlackWins += 1;
    }
};

