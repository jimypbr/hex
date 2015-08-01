
#include <utility>		// std::pair
#include <random>
#include <functional> 	// std::bind
#include <algorithm> 	// std::shuffle
#include <iterator>		// std::distance
#include <iostream>
#include "board.h"
#include "hexGraph.h"
#include "pureMonteCarloPlayer.h"

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

#define NITER 2000

std::pair<int,int> PureMonteCarloPlayer:: nextMove(HexBoard board, const HexGraph& hex_graph) const
{
	EmptyTiles empty_tiles = getEmptyTiles_(board);
	int nempty = empty_tiles.sub_board.size();

	std::vector<double> next_move_score(nempty,0);

	// iterate through next possible moves for black and do monte carlo for each
	const int niter = NITER;
	for (int i=0; i<nempty; ++i)
	{
		int trial_move = empty_tiles.coords[i];
		HexBoard trial_board = board;
		trial_board[trial_move] = TileColour::BLACK;
		next_move_score[i] = simulatePlay_(trial_board, hex_graph, niter);
	}

	// debug
	/*
	for (int i=0; i<nempty; ++i)
	{
		std::cout << next_move_score[i] << ", ";
	}
	std::cout << std::endl;
	*/

	// return coord with highest next move score
	int addr_empty = std::distance(next_move_score.begin(), std::max_element(next_move_score.begin(), next_move_score.end()) );
	int addr = empty_tiles.coords[addr_empty];
	int row = addr / board.side();
	int col = addr % board.side();

	std::pair<int, int> next_move_coord(row, col);

	return next_move_coord;
}

/*
 * Given a partially filled hex board, return the win/lose ratio for the aiplayer after niter number
 * of monteCarlo trials, which randomly fill the rest of the baord and then calculates who won.
 */
double PureMonteCarloPlayer:: simulatePlay_(HexBoard &board, const HexGraph &hex_graph, const int niter) const
{
	EmptyTiles empty_tiles = getEmptyTiles_(board);
	int nempty = empty_tiles.sub_board.size();

	// assume white goes first
	int nblack_left = nempty / 2;

	// fill up the empty_tiles with black and white
	for (int i=0; i<nblack_left; ++i)
	{
		empty_tiles.sub_board[i] = TileColour::BLACK;
	}
	for (int i=nblack_left; i<nempty; ++i)
	{
		empty_tiles.sub_board[i] = TileColour::WHITE;
	}

	// perform monte carlo iterations
	// shuffle subboard, reinsert, and evaluate winner

	int nblack_wins = 0;
	for (int i=0; i<niter; ++i)
	{
		std::shuffle(empty_tiles.sub_board.begin(), empty_tiles.sub_board.end(), rng);
		insertSubBoard_(empty_tiles, board);
		TileColour winner = hex_graph.fullBoardWinner(board);

		if (winner == TileColour::BLACK)
			nblack_wins++;
	}

	return (double) nblack_wins / (double) niter;
}

inline void PureMonteCarloPlayer:: insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const
{
	// gather subboard into board
	int nempty = empty_tiles.sub_board.size();

	for (int i=0; i<nempty; ++i)
	{
		const int addr = empty_tiles.coords[i];
		board[addr] = empty_tiles.sub_board[i];
	}
}

inline std::pair<int,int> PureMonteCarloPlayer:: randomMove_(HexBoard& board) const
{
	std::uniform_int_distribution<int> rng_uniform(0,board.side()-1);
	auto random_coord = std::bind ( rng_uniform, rng_ );

	int row, col;
	for (;;)
	{
		row = random_coord();
		col = random_coord();

		if (board[row*board.side() + col] == TileColour::EMPTY)
		{
			break;
		}
	}

	std::pair<int,int> coord = {row, col};
	return coord;
}

EmptyTiles PureMonteCarloPlayer:: getEmptyTiles_(const HexBoard& board) const
{
	// count # of empty tiles
	int n_empty = 0;
	for (int tile = 0; tile < board.ntiles(); ++tile)
	{
		if (board[tile] == TileColour::EMPTY)
		{
			n_empty++;
		}
	}

	std::vector<int> coords(n_empty);
	std::vector<TileColour> sub_board(n_empty, TileColour::EMPTY);

	// coords of emtpy tiles
	int side = board.side();
	int k=0;
	for (int i=0; i<side; i++)
	{
		for (int j=0; j<side; j++)
		{
			const int addr = i*side+j;
			if (board[addr] == TileColour::EMPTY)
			{
				coords[k] = addr;
				k++;
			}
		}
	}

	// pack both vectors into EmptyTiles struct and copy out
	EmptyTiles et;
	et.coords = std::move(coords);
	et.sub_board = std::move(sub_board);

	return et;
}

