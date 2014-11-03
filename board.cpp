
#include <vector>
#include <ostream>
#include "board.hpp"

Hex_Board::Hex_Board(int s) : N(s), N2(s*s), tiles(s*s), nEmpty(s*s)
{
	for (auto &it : tiles)
		it = EMPTY;
}
Hex_Board::Hex_Board() : N(5), N2(5*5), tiles(5*5), nEmpty(5*5)
{
	for (auto &it : tiles)
		it = EMPTY;
}

std::ostream& operator<< (std::ostream& out, const Hex_Board& board)
{
	// draw the board
	out << "   A  B  C  D  E" << std::endl;

	for (int i=0; i<board.N; ++i)
	{
		out << i+1 << "   ";
		for (int j=0; j<board.N; ++j)
		{
			int tile = board.tiles[i*board.N+j];
			if (tile == WHITE)
				out << "W ";
			else if (tile == BLACK)
				out << "B  ";
			else
				out << ".  ";
		}
		out << " " << i+1 << std::endl;
		out << std::string(i+1,' ');	// indent next row
	}
	out << "   A  B  C  D  E" << std::endl;
}
