#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "hexGraph.h"
#include "board.h"
#include "aiplayer.h"
#include "mcNode.h"


/**
 * AI Hex player that uses the Monte Carlo Tree Search algorithm (see mcts.ai).
 * The MCTS uses the Upper Confidence Bound for Trees (UCT) method.
 */
class MCSearchTreePlayer : public AIPlayer
{
private:

    const double EPSILON_ = 1e-6;

    std::uniform_real_distribution<double> rng_double_;
    std::default_random_engine rng_;

    MCNode* select_(MCNode* node) const;
    MCNode* expand_(MCNode* node) const;
    MCNode* bestMove_(MCNode* node) const;
    TileColour trialGame_(MCNode* node) const;

public:
    MCSearchTreePlayer() : rng_double_(0,1)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }

    std::pair<int, int> nextMove(HexBoard board) const override;
};

