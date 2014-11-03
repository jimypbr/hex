
#include <iostream>
#include <string>
#include "board.hpp"
#include "cli_hex.hpp"

// constructor
CLI_Hex::CLI_Hex() : game_size(5), board(5) {}

void CLI_Hex :: play_game()
{
	// draw the board
	std::cout << board << std::endl;
}

