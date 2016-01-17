//
// Created by James on 01/10/15.
//

#include <utility>
#include <random>
#include <algorithm>
#include <iterator>
#include "board.h"
#include "subBoard.h"
#include "hexGraph.h"
#include "pureMonteCarlo.h"

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

#define NITER 2500

std::pair<int, int> PureMonteCarlo::nextMove(Board &board, TileColour ai_colour, bool is_first) const
{
    SubBoard empty_sub_board = getEmptySubBoard(board);
    int nempty = empty_sub_board.pieces.size();

    std::vector<double> next_move_score(nempty,0);

    // iterate through next possible moves for black and do monte carlo for each
    const int niter = NITER;
    for (int i = 0; i < nempty; ++i)
    {
        int trial_move = empty_sub_board.coords[i];
        Board trial_board = board;
        trial_board[trial_move] = ai_colour;
        next_move_score[i] = simulatePlay_(trial_board, niter, ai_colour, is_first);
    }

    // return coord with highest next move score
    int addr_best = std::distance(next_move_score.begin(), std::max_element(next_move_score.begin(), next_move_score.end()) );
    int best_pos = empty_sub_board.coords[addr_best];
    int row = best_pos / board.side() + 1;
    int col = best_pos % board.side() + 1;

    return std::pair<int, int>(row, col);
}

double PureMonteCarlo::opponentWinChance(Board &board, TileColour opponent_colour, bool is_first) const
{
    return 0.0;
}

/*
 * Given a partially filled hex board, return the win/lose ratio for the aiplayer after niter number
 * of monteCarlo trials, which randomly fill the rest of the baord and then calculates who won.
 */
double PureMonteCarlo :: simulatePlay_(Board &board, const int niter, TileColour ai_colour, bool is_first) const
{
    SubBoard sub_board = getEmptySubBoard(board);
    int nempty = sub_board.pieces.size();

    // determine colour of first and second player
    // to decide how many different colour pieces fill the board

    TileColour colour_player2;
    if (is_first)
        colour_player2 = oppositeColour(ai_colour);
    else
        colour_player2 = ai_colour;
    TileColour colour_player1 = oppositeColour(colour_player2);

    int nplayer2 = nempty / 2;

    // fill up the empty_tiles with black and white
    for (int i = 0; i < nplayer2; ++i)
    {
        sub_board.pieces[i] = colour_player2;
    }
    for (int i = nplayer2; i < nempty; ++i)
    {
        sub_board.pieces[i] = colour_player1;
    }

    // perform monte carlo iterations
    // shuffle subboard, reinsert, and evaluate winner

    int nAI_wins = 0;
    for (int i = 0; i < niter; ++i)
    {
        std::shuffle(sub_board.pieces.begin(), sub_board.pieces.end(), rng);
        insertSubBoard(sub_board, board);
        TileColour winner = HexGraph::fullBoardWinner(board);

        if (winner == ai_colour)
            nAI_wins++;
    }

    return (double) nAI_wins / (double) niter;
}
