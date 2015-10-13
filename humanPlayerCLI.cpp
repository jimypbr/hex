//
// Created by James on 30/09/15.
//

#include <utility>
#include <iostream>
#include <limits>
#include "humanPlayerCLI.h"

std::pair<int, int> HumanPlayerCLI::nextMove(Board &board) const
{
    std::pair<int,int> nextPos;

    while (true)
    {
        std::cout << "Enter x, y coordinates: x y" << std::endl;
        auto pos = cliInput_(board);

        if (validInput_(board, pos.first, pos.second))
        {
            nextPos = pos;
            break;
        }
        else
        {
            std::cout << "That's not a valid move. Try again." << std::endl;
        }
    }
    return nextPos;
}

bool HumanPlayerCLI::playPieRule(Board &board) const
{
    return false;
}

bool HumanPlayerCLI::validInput_(Board &board, int x, int y) const
{
    int side = board.side();
    if (x > side || x < 1)
    {
        return false;
    }

    if (y > side || y < 1)
    {
        return false;
    }

    int i = x - 1;
    int j = y - 1;
    if (board[i*side + j] != TileColour::EMPTY)
    {
        return false;
    }

    return true;
}

std::pair<int,int> HumanPlayerCLI::cliInput_(Board &board) const
{
    int x, y;
    std::cin >> x >> y;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::pair<int,int>(x, y);
}
