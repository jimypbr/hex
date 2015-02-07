
#include <iostream>
#include "board.h"
#include "cli_hex.h"

void CLI_Hex :: gameLoop()
{
	startGame_();

	printBoard_();

	// main loop
	for (;;)
	{
		userInputMove_();
        if (game_.isFinished()) break;
		game_.aiMove();
		clearScreen_();
		printBoard_();
        if (game_.isFinished()) break;
	}
	std::cout << "Game finished!!" << std::endl;

	// print the winner
	TileColour winner = game_.winner();	

	printWinner_(winner);
}

inline void CLI_Hex :: startGame_()
{
	std::cout << "###########" << std::endl;
	std::cout << "### HEX ###" << std::endl;
	std::cout << "###########" << std::endl;
	std::cout << std::endl;

	int s;
	while ( (std::cout << "Enter game board size: " << std::endl) \
			&& (!(std::cin >> s) || !(validGameSize_(s)) )
		  )
	{
		std::cout << "That's not a valid size. Try again." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// initalise internals with the size
	board_side_ = s;
	game_ = HexGame(s);
}

inline bool CLI_Hex :: validGameSize_(int s)
{
	if (s < 3)
		return false;
	else if (s > 19)
		return false;
	else if (s%2 == 0)
		return false;
	else
		return true;
}

inline void CLI_Hex :: userInputMove_()
{
	int x, y;

	while ( (std::cout << "Enter x, y coordinates: x y" << std::endl) \
			&& (!(std::cin >> x >> y) \
			|| !(game_.move(x, y)) )
		  )
	{
		std::cout << "That's not a valid move. Try again." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}	
}

inline void CLI_Hex :: printBoard_()
{
	auto board = game_.get_main_board();

	std::cout << "   A  B  C  D  E" << std::endl;

	for (int row=0; row < board_side_; ++row)
	{
		std::cout << row+1 << "   ";
		for (int col=0; col < board_side_; ++col)
		{
			TileColour tile = board[row*board_side_+col];
			if (tile == TileColour::WHITE)
				std::cout << "W  ";
			else if (tile == TileColour::BLACK)
				std::cout << "B  ";
			else
				std::cout << "-  ";
		}
		std::cout << " " << row+1 << std::endl;
		std::cout << std::string(row+1,' ');	// indent next row
	}
	std::cout << "   A  B  C  D  E" << std::endl;
	std::cout << std::endl;
}

inline void CLI_Hex :: printWinner_(TileColour winner)
{
	switch (winner)
	{
		case TileColour::WHITE:
			std::cout << "Winner is USER (WHITE)!" << std::endl;
			break;
		case TileColour::BLACK:
			std::cout << "Winner is AI (BLACK)!" << std::endl;
			break;
		default:
			std::cout << "Winner is wat" << std::endl;
			break;
	}
}

inline void CLI_Hex :: clearScreen_()
{
	// hacky but works
	//std::cout << std::string (100, '\n');
    std::cout << std::string (2, '\n');
}
