//
// Created by James on 01/10/15.
//

#ifndef HEX_MONTECARLOTREESEARCH_H
#define HEX_MONTECARLOTREESEARCH_H

#include <utility>
#include <random>
#include "board.h"
#include "aiStrategy.h"

class MonteCarloTreeSearch : public AIStrategy
{
private:

    /**
     * Private Node class in Monte Carlo search tree that represents
     * a possible board configuration.
    */
    struct MCNode
    {
        int nWhiteWins = 0;
        int nBlackWins = 0;
        int nVisits = 0;
        int nEmpty;
        int move;

        Board game;
        TileColour colour;

        std::vector<std::unique_ptr<MCNode>> children;

        MCNode(Board game, TileColour col) : game(game), colour(col)
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

    const double EPSILON_ = 1e-6;

    std::uniform_real_distribution<double> rng_double_;
    std::default_random_engine rng_;

    MCNode* select_(MCNode* node, TileColour ai_colour) const;
    void expand_(MCNode* node) const;
    MCNode* bestMove_(MCNode* node) const;
    TileColour trialGame_(MCNode* node, TileColour ai_colour, bool is_first) const;

public:
    MonteCarloTreeSearch() {}
    std::pair<int, int> nextMove(Board &board, TileColour ai_colour, bool is_first) const override;
    double opponentWinChance(Board &board, TileColour opponent_colour, bool is_first) const override;
};
#endif //HEX_MONTECARLOTREESEARCH_H
