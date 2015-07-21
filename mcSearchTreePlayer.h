#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"
#include "aiplayer.h"

struct MCNode
{
    int whiteWins = 0;
    int blackWins = 0;
    HexBoard board;

    std::vector<MCNode*> children;
};

class MCSearchTreePlayer : public AIPlayer
{
private:

    std::uniform_int_distribution<int> rng_uniform_;
    std::default_random_engine rng_;
    void insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const;
    EmptyTiles getEmptyTiles_(const HexBoard& board) const;

public:
    MCSearchTree(int s) : AIPlayer(s)
    {
    }

    std::pair<int, int> nextMove(HexBoard board, const HexGraph &hex_graph) const override;
};

