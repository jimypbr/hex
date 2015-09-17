#pragma once

#include <utility>
#include <random>
#include <chrono>
#include "aiPlayer.h"
#include "hexGraph.h"
#include "board.h"


/**
 * AI Hex player that uses a pure Monte Carlo algorithm.
 */
class PureMonteCarloPlayer : public AIPlayer
{
private:
    TileColour ai_colour_;
    bool first_player_;

    std::default_random_engine rng_;
    double simulatePlay_(HexBoard &board, const int niter) const;

public:
    PureMonteCarloPlayer() : ai_colour_(TileColour::BLACK)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    PureMonteCarloPlayer(TileColour c, bool first_player) : ai_colour_(c), first_player_(first_player)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    std::pair<int,int> nextMove(HexBoard board) const override;
};
