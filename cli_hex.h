#pragma once

#include "game.h"

class CLI_Hex
{
	private:
		HexGame game_;
		int board_side_;
		void startGame_();
		void userInputMove_();
		void printBoard_();
		bool validGameSize_(int s);
		void printWinner_(TileColour winner);

	public:
		CLI_Hex() : game_(7), board_side_(7) {}
		void gameLoop();
};
