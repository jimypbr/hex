#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "aiPlayer.h"
#include "hexGraph.h"
#include "board.h"

struct EmptyTiles
{
    std::vector<int> coords;
    HexBoard sub_board;
};

class PureMonteCarlo : public AIPlayer
{
private:
    std::uniform_int_distribution<int> rng_uniform_;
    std::default_random_engine rng_;
    double monteCarloScore_(HexBoard &board, const HexGraph &hex_graph, const int niter) const;
    void insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const;
    EmptyTiles getEmptyTiles_(const HexBoard& board) const;
    std::pair<int,int> randomMove_(HexBoard& board) const;

public:
    PureMonteCarlo (int s) : AIPlayer(s), rng_uniform_(0,s-1)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    std::pair<int,int> nextMove(HexBoard board, const HexGraph& hex_graph) const;
};
