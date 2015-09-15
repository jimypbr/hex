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
    std::default_random_engine rng_;
    double simulatePlay_(HexBoard &board, const int niter) const;
    std::pair<int,int> randomMove_(HexBoard& board) const;

public:
    PureMonteCarloPlayer()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng_.seed(seed);
    }
    std::pair<int,int> nextMove(HexBoard board) const override;
};
