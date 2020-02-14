
#include <iostream>
#include "game.h"

bool HexGame::isFinished() const
{
	bool whiteWon = HexGraph::whiteWon(main_board_);
	bool blackWon = HexGraph::blackWon(main_board_);
	return (whiteWon || blackWon);
}

TileColour HexGame::winner() const
{
	if (HexGraph::whiteWon(main_board_))
		return TileColour::WHITE;
	else if (HexGraph::blackWon(main_board_))
		return TileColour::BLACK;
	else
		return TileColour::EMPTY;
}

void HexGame::movePlayer1()
{
	auto pos = p1_->nextMove(main_board_);
	main_board_(pos.first, pos.second) = p1_colour_;
}

void HexGame::movePlayer2()
{
	auto pos = p2_->nextMove(main_board_);
	main_board_(pos.first, pos.second) = p2_colour_;
}
