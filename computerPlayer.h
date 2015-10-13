//
// Created by James on 30/09/15.
//

#ifndef HEX_COMPUTERPLAYER_H
#define HEX_COMPUTERPLAYER_H

#include <memory>
#include <utility>
#include "board.h"
#include "aiStrategy.h"
#include "aiStrategyEnum.h"
#include "pureMonteCarlo.h"
#include "monteCarloTreeSearch.h"
#include "player.h"

class ComputerPlayer : public Player
{
private:
    TileColour colour_;
    std::unique_ptr<AIStrategy> strategy_;
    bool is_first_;

public:
    ComputerPlayer(TileColour colour, AIStrategyEnum strategy, bool is_first) : colour_(colour), is_first_(is_first)
    {
        if (strategy == AIStrategyEnum::PURE_MC)
        {
            strategy_ = std::unique_ptr<AIStrategy>(new PureMonteCarlo());
        }
        else if (strategy == AIStrategyEnum::MCTS)
        {
            strategy_ = std::unique_ptr<AIStrategy>(new MonteCarloTreeSearch());
        }
    }
    std::pair<int, int> nextMove(Board &board) const override;
    bool playPieRule(Board &board) const override;
};

#endif //HEX_COMPUTERPLAYER_H
