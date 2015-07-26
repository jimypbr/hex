#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "aiPlayer.h"
#include "hexGraph.h"
#include "board.h"


class PureMonteCarloPlayer : public AIPlayer
{
private:
    std::default_random_engine rng_;
    double simulatePlay_(HexBoard &board, const HexGraph &hex_graph, const int niter) const;
    void insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const;
    EmptyTiles getEmptyTiles_(const HexBoard& board) const;
    std::pair<int,int> randomMove_(HexBoard& board) const;

public:
    PureMonteCarloPlayer() : AIPlayer()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    std::pair<int,int> nextMove(HexBoard board, const HexGraph& hex_graph) const override;
};
