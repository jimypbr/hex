#ifndef H_CLI
#define H_CLI

#include "board.hpp"

class CLI_Hex
{
	private:
		int game_size;
		Hex_Board board;
	public:
		CLI_Hex();
		void play_game();
};

#endif
