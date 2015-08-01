#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"
#include "aiplayer.h"
#include "mcNode.h"


class MCSearchTreePlayer : public AIPlayer
{
private:

    const double EPSILON_ = 1e-6;

    //std::uniform_int_distribution<int> rng_uniform_;
    std::uniform_real_distribution<double> rng_double_;
    std::default_random_engine rng_;

    void insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const;
    EmptyTiles getEmptyTiles_(const HexBoard& board) const;
    MCNode* select_(MCNode* node) const;
    MCNode* expand_(MCNode* node) const;
    TileColour trialGame_(MCNode* node, const HexGraph & hex_graph) const;

public:
    MCSearchTreePlayer() : AIPlayer(), rng_double_(0,1)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }

    std::pair<int, int> nextMove(HexBoard board, const HexGraph &hex_graph) const override;
};

