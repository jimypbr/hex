#ifndef H_HEXBOARD
#define H_HEXBOARD

#include <vector>

enum tile_colour_t {EMPTY, WHITE, BLACK};

class Hex_Board
{
	private:
		std::vector<tile_colour_t> tiles;
		int N;		// length of side of hex board
		int N2;		// N**2
		int nEmpty;

	public:
		Hex_Board(int s);
		Hex_Board();
		void place_piece(tile_colour_t colour, int x, int y);
		bool valid_coord(int x, int y);
		friend std::ostream& operator<< (std::ostream& out, const Hex_Board& board);
};

#endif
