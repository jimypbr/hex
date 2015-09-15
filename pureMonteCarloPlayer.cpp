
#include <utility>		// std::pair
#include <random>
#include <functional> 	// std::bind
#include <algorithm> 	// std::shuffle
#include <iterator>		// std::distance
#include <iostream>
#include "board.h"
#include "hexGraph.h"
#include "pureMonteCarloPlayer.h"
#include "subBoard.h"

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

#define NITER 2000

std::pair<int,int> PureMonteCarloPlayer:: nextMove(HexBoard board) const
{
    SubHexBoard empty_sub_board = getEmptySubHexBoard(board);
    int nempty = empty_sub_board.colours.size();

	std::vector<double> next_move_score(nempty,0);

	// iterate through next possible moves for black and do monte carlo for each
	const int niter = NITER;
	for (int i=0; i<nempty; ++i)
	{
		int trial_move = empty_sub_board.coords[i];
		HexBoard trial_board = board;
		trial_board[trial_move] = TileColour::BLACK;
		next_move_score[i] = simulatePlay_(trial_board, niter);
	}

	// return coord with highest next move score
	int addr_best = std::distance(next_move_score.begin(), std::max_element(next_move_score.begin(), next_move_score.end()) );
	int best_pos = empty_sub_board.coords[addr_best];
	int row = best_pos / board.side();
	int col = best_pos % board.side();

	std::pair<int, int> next_move_coord(row, col);

	return next_move_coord;
}

/*
 * Given a partially filled hex board, return the win/lose ratio for the aiplayer after niter number
 * of monteCarlo trials, which randomly fill the rest of the baord and then calculates who won.
 */
double PureMonteCarloPlayer:: simulatePlay_(HexBoard &board, const int niter) const
{
    SubHexBoard sub_board = getEmptySubHexBoard(board);
    int nempty = sub_board.colours.size();

	// assume white goes first
	int nblack_left = nempty / 2;

	// fill up the empty_tiles with black and white
	for (int i=0; i<nblack_left; ++i)
	{
		sub_board.colours[i] = TileColour::BLACK;
	}
	for (int i=nblack_left; i<nempty; ++i)
	{
		sub_board.colours[i] = TileColour::WHITE;
	}

	// perform monte carlo iterations
	// shuffle subboard, reinsert, and evaluate winner

	int nblack_wins = 0;
	for (int i=0; i<niter; ++i)
	{
		std::shuffle(sub_board.colours.begin(), sub_board.colours.end(), rng);
		insertSubHexBoard(sub_board, board);
		TileColour winner = HexGraph::fullBoardWinner(board);

		if (winner == TileColour::BLACK)
			nblack_wins++;
	}

	return (double) nblack_wins / (double) niter;
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

