
#include <iostream>
#include "game.h"

bool HexGame :: move(int x, int y)
{
	int i = x-1;
	int j = y-1;

	// evaluate move legality
	if (x > side_ || x < 1)
	{
		return false;
	}

	if (y > side_ || y < 1)
	{
		return false;
	}

	if (main_board_[i*side_ + j] != TileColour::EMPTY)
	{
		return false;
	}

	main_board_[i*side_ + j] = TileColour::WHITE;
	return true;
}

void HexGame :: aiMove()
{
	std::pair<int,int> coord = ai_.nextMove(main_board_, hgraph_);
	main_board_[coord.first * side_ + coord.second] = TileColour::BLACK;
}

bool HexGame :: isFinished() const
{
	bool whiteWon = hgraph_.whiteWon(main_board_);
    std::cout << "whiteWon = " << whiteWon << std::endl;
	bool blackWon = hgraph_.blackWon(main_board_);
    std::cout << "blackWon = " << blackWon << std::endl;
	return (whiteWon || blackWon);
}

TileColour HexGame :: winner() const
{
	if ( hgraph_.whiteWon(main_board_) )
		return TileColour::WHITE;
	else if ( hgraph_.blackWon(main_board_) )
		return TileColour::BLACK;
	else 
		return TileColour::EMPTY;
}

