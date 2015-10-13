//
// Created by James on 01/10/15.
//

#ifndef HEX_MONTECARLOTREESEARCH_H
#define HEX_MONTECARLOTREESEARCH_H

#include <utility>
#include <random>
#include "board.h"
#include "mcNode.h"
#include "aiStrategy.h"

class MonteCarloTreeSearch : public AIStrategy
{
private:
    const double EPSILON_ = 1e-6;

    std::uniform_real_distribution<double> rng_double_;
    std::default_random_engine rng_;

    MCNode* select_(MCNode* node, TileColour ai_colour) const;
    MCNode* expand_(MCNode* node) const;
    MCNode* bestMove_(MCNode* node) const;
    TileColour trialGame_(MCNode* node, TileColour ai_colour, bool is_first) const;

public:
    MonteCarloTreeSearch() {}
    std::pair<int, int> nextMove(Board &board, TileColour ai_colour, bool is_first) const override;
    double opponentWinChance(Board &board, TileColour opponent_colour, bool is_first) const override;
};
#endif //HEX_MONTECARLOTREESEARCH_H
