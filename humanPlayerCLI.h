//
// Created by James on 30/09/15.
//

#ifndef HEX_HUMANPLAYERCLI_H
#define HEX_HUMANPLAYERCLI_H

#include <utility>
#include "board.h"
#include "player.h"

class HumanPlayerCLI : public Player
{
private:
    TileColour colour_;
    bool validInput_(Board &board, int x, int y) const;
    std::pair<int, int> cliInput_(Board &board) const;

public:
    HumanPlayerCLI(TileColour colour) : colour_(colour) {}

    std::pair<int, int> nextMove(Board &board) const override;
    bool playPieRule(Board &board) const override;
};

#endif //HEX_HUMANPLAYERCLI_H
