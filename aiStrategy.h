//
// Created by James on 30/09/15.
//

#ifndef HEX_AISTRATEGY_H
#define HEX_AISTRATEGY_H

#include <utility>
#include "board.h"

class AIStrategy
{
public:
    virtual std::pair<int, int> nextMove(Board &board, TileColour ai_colour, bool is_first) const = 0;
    virtual double opponentWinChance(Board &board, TileColour opponent_colour, bool is_first) const = 0;
};

#endif //HEX_AISTRATEGY_H
