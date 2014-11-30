#pragma once

#include <vector>

enum class TileColour {EMPTY, WHITE, BLACK};

typedef std::vector<TileColour> HexBoard;
/*
class Hex_Board
{
	private:
		std::vector<tile_colour_t> tiles;

	public:
		Hex_Board(int s) : tiles(s*s)
		{
			for (auto &it : tiles)
				it = EMPTY;
		}
		Hex_Board() : tiles(5*5)
		{
			for (auto &it : tiles)
				it = EMPTY;
		}
		void place_piece(tile_colour_t colour, int x, int y);
		bool valid_coord(int x, int y);
		friend std::ostream& operator<< (std::ostream& out, const Hex_Board& board);
};
*/
