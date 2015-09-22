
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

#define NITER 200

std::pair<int,int> PureMonteCarloPlayer:: nextMove(Board board) const
{
    SubBoard empty_sub_board = getEmptySubBoard(board);
    int nempty = empty_sub_board.colours.size();

	std::vector<double> next_move_score(nempty,0);

	// iterate through next possible moves for black and do monte carlo for each
	const int niter = NITER;
	for (int i = 0; i < nempty; ++i)
	{
		int trial_move = empty_sub_board.coords[i];
		Board trial_board = board;
		trial_board[trial_move] = ai_colour_;
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
double PureMonteCarloPlayer:: simulatePlay_(Board &board, const int niter) const
{
    SubBoard sub_board = getEmptySubBoard(board);
    int nempty = sub_board.colours.size();

	TileColour colour_player2;
	if (first_player_)
		colour_player2 = oppositeColour(ai_colour_);
	else
		colour_player2 = ai_colour_;
	TileColour colour_player1 = oppositeColour(colour_player2);

	int nplayer2 = nempty / 2;

	// fill up the empty_tiles with black and white
	for (int i = 0; i < nplayer2; ++i)
	{
		sub_board.colours[i] = colour_player2;
	}
	for (int i = nplayer2; i < nempty; ++i)
	{
		sub_board.colours[i] = colour_player1;
	}

	// perform monte carlo iterations
	// shuffle subboard, reinsert, and evaluate winner

	int nAI_wins = 0;
	for (int i = 0; i < niter; ++i)
	{
		std::shuffle(sub_board.colours.begin(), sub_board.colours.end(), rng);
		insertSubBoard(sub_board, board);
		TileColour winner = HexGraph::fullBoardWinner(board);

		if (winner == ai_colour_)
			nAI_wins++;
	}

	return (double) nAI_wins / (double) niter;
}
