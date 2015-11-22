
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
		game_.movePlayer1();
        if (game_.isFinished()) break;
		clearScreen_();
		printBoard_();
		game_.movePlayer2();
		clearScreen_();
		printBoard_();
        if (game_.isFinished()) break;
	}
	std::cout << "Game finished!!" << std::endl;

	// print the winner
	clearScreen_();
	printBoard_();
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
	game_ = HexGame(s, std::unique_ptr<Player>(new HumanPlayerCLI(TileColour::WHITE)),
					std::unique_ptr<Player>(new ComputerPlayer(TileColour::BLACK, AIStrategyEnum::MCTS, false)));
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

inline void CLI_Hex :: printBoard_()
{
	auto board = game_.get_main_board();

	std::cout << "   ";
	for (int col = 0; col < board_side_; ++col)
    {
        std::cout.width(3);
        std::cout << std::left << col + 1;
    }
	std::cout << std::endl;

	for (int row=0; row < board_side_; ++row)
	{
        std::cout.width(4);
        std::cout << std::left << row+1;

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
	std::cout << "    ";
	for (int col = 0; col < board_side_; ++col)
    {
        std::cout.width(3);
        std::cout << std::left << col + 1;
    }
    std::cout << std::endl;
}

inline void CLI_Hex :: printWinner_(TileColour winner)
{
	switch (winner)
	{
		case TileColour::WHITE:
			std::cout << "Winner is WHITE!" << std::endl;
			break;
		case TileColour::BLACK:
			std::cout << "Winner is BLACK!" << std::endl;
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
