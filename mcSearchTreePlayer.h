#pragma once

#include <utility>
#include <random>
#include <chrono>
#include <memory>
#include <vector>
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

    /**
     * This AIPlayers colour.
     * */
    TileColour ai_colour_;
    bool first_player_;

    std::uniform_real_distribution<double> rng_double_;
    std::default_random_engine rng_;

    MCNode* select_(MCNode* node) const;
    MCNode* expand_(MCNode* node) const;
    MCNode* bestMove_(MCNode* node) const;
    TileColour trialGame_(MCNode* node) const;

public:
    MCSearchTreePlayer() : ai_colour_(TileColour::BLACK), rng_double_(0,1)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    MCSearchTreePlayer(TileColour c, bool first_player) : ai_colour_(c), first_player_(first_player), rng_double_(0,1)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }

    std::pair<int, int> nextMove(HexBoard board) const override;
};

