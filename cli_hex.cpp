
#include <iostream>
#include <string>
#include <limits>
#include "board.hpp"
#include "cli_hex.hpp"

// constructor
CLI_Hex::CLI_Hex() : game_size(6), board(6) {}

void CLI_Hex :: play_game()
{
	int x, y;

	// draw the board
	std::cout << board << std::endl;

	x = y = 0;

	while ( (std::cout << "Enter x, y coordinates: x y" << std::endl) 
			&& (!(std::cin >> x >> y) || !(board.valid_coord(x, y)) ) 
		  )
	{
		std::cout << "That's not a valid move. Try again.";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}	
	/*
	while (1)
	{
		int x_, y_;
		std::cout << "Enter x, y coordinates: x y" << std::endl;
		if (std::cin >> x_ >> y_)
		{
			std::cout << x_ << " " << y_ << std::endl;
			bool is_valid = board.valid_coord(x_, y_);
			if (is_valid) {
				x = x_;
				y = y_;
				break;
			}
		}
		else
		{
			std::cout << "Invalid coords entered. Try again!" << std::endl;
			std::cin.clear();
		}
	}
	*/
	board.place_piece(WHITE, x, y);
	std::cout << board << std::endl;
}
