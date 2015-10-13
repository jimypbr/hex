//
// Created by James on 30/09/15.
//

#include <utility>
#include "board.h"
#include "aiStrategy.h"
#include "computerPlayer.h"

std::pair<int, int> ComputerPlayer::nextMove(Board &board) const
{
    return strategy_->nextMove(board, colour_, is_first_);
}

bool ComputerPlayer::playPieRule(Board &board) const
{
    return false;
}
