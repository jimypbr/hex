#ifndef H_HEXBOARD
#define H_HEXBOARD

#include <vector>

enum tile_state_t {EMPTY, WHITE, BLACK};

class Hex_Board
{
	private:
		std::vector<tile_state_t> tiles;
		int N;		// length of side of hex board
		int N2;		// N**2
		int nEmpty;

	public:
		Hex_Board(int s);
		Hex_Board();
		friend std::ostream& operator<< (std::ostream& out, const Hex_Board& board);
};

#endif
