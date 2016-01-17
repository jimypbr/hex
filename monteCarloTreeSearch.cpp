//
// Created by James on 01/10/15.
//

#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include "board.h"
#include "subBoard.h"
#include "hexGraph.h"
#include "monteCarloTreeSearch.h"

static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

std::pair<int, int> MonteCarloTreeSearch::nextMove(Board &board, TileColour ai_colour, bool is_first) const
{
    const int Niter = 2000;

    auto root = std::unique_ptr<MCNode>(new MCNode(board, oppositeColour(ai_colour)));

    int count = 0;
    for (int i = 0; i < board.ntiles(); ++i)
    {
        if (board[i] == TileColour::EMPTY)
            count++;
    }
    root->nEmpty = count;
    expand_(root.get());

    for (int i = 0; i < Niter; ++i)
    {
        // data structure to record line of play
        std::vector<MCNode*> visited;

        // select node to expand
        MCNode* cur = root.get();
        visited.push_back(cur);

        // find best leaf to expand
        while ( !(*cur).isLeaf() )
        {
            cur = select_(cur, ai_colour);
            visited.push_back(cur);
        }
        // is terminal node?
        if (cur->nEmpty == 0)
        {
            // update stats or not??
            TileColour winner = HexGraph::fullBoardWinner(cur->game);
            for (const auto &node : visited)
                node->updateStats(winner);
            continue;
        }
        expand_(cur);

        MCNode* newNode = select_(cur, ai_colour);
        visited.push_back(newNode);

        for (int t = 0; t < 30; ++t)
        {
            TileColour winner = trialGame_(newNode, ai_colour, is_first);

            for (const auto &node : visited)
                node->updateStats(winner);
        }
    }

    // Select the node that gave the best score
    MCNode* best_node = bestMove_(root.get());

    // Return that node's move
    int move = best_node->move;
    return std::pair<int, int>(move / board.side() + 1, (move % board.side()) + 1);
}

double MonteCarloTreeSearch::opponentWinChance(Board &board, TileColour opponent_colour, bool is_first) const
{
    return 0.0;
}

MonteCarloTreeSearch::MCNode* MonteCarloTreeSearch::bestMove_(MCNode* node) const
{
    double best_score = -1;
    MonteCarloTreeSearch::MCNode* best_node = nullptr;
    int total_visits = 0;
    for (const auto& c : node->children)
    {
        double score;
        if (node->colour == TileColour::WHITE)
            score = c->nBlackWins / (double) c->nVisits;
        else
            score = c->nWhiteWins / (double) c->nVisits;

        total_visits += c->nVisits;

        if (score > best_score)
        {
            best_score = score;
            best_node = c.get();
        }
    }
    //std::cout << "Total visits = " << total_visits << std::endl;
    return best_node;
}

MonteCarloTreeSearch::MCNode* MonteCarloTreeSearch::select_(MCNode* node, TileColour ai_colour) const
{
    MonteCarloTreeSearch::MCNode* selected = nullptr;
    double bestValue = -1.0;

    // use rng to break ties
    std::uniform_real_distribution<double> uniform_double(0,1);
    auto ran = std::bind(uniform_double, rng);

    // select node child with best uctValue. Use small random number
    // to break ties.
    for (auto const& cptr : node->children )
    {
        auto c = cptr.get();

        int nAIWins;
        if (ai_colour == TileColour::BLACK)
            nAIWins = c->nBlackWins;
        else
            nAIWins = c->nWhiteWins;

        double uctValue = nAIWins / (c->nVisits + EPSILON_) + \
                        sqrt( log( node->nVisits+1) / (c->nVisits + EPSILON_)) + ran()*EPSILON_ ;
        if (uctValue > bestValue)
        {
            selected = c;
            bestValue = uctValue;
        }
    }
    return selected;
}

MonteCarloTreeSearch::MCNode* MonteCarloTreeSearch::expand_(MCNode* node) const
{
    SubBoard next_moves = getEmptySubBoard(node->game);
    const int n = next_moves.coords.size();
    TileColour child_colour = oppositeColour(node->colour);

    for (int i = 0; i < n; ++i)
    {
        node->children.push_back( std::unique_ptr<MonteCarloTreeSearch::MCNode>(new MonteCarloTreeSearch::MCNode( node->game, child_colour ) ));
    }

    // populate children with next possible moves
    for (int i = 0; i < n; ++i)
    {
        auto const& c = node->children[i];
        c->game[next_moves.coords[i]] = child_colour;
        c->move = next_moves.coords[i];
        c->nEmpty = n-1;
    }

    // return random next move
    std::uniform_int_distribution<int> uniform_int(0,n-1);
    auto ran = std::bind(uniform_int, rng_);
    int next = ran();

    auto cptr = node->children[next].get();
    return cptr;
}

TileColour MonteCarloTreeSearch::trialGame_(MCNode* node, TileColour ai_colour, bool first_player) const
{
    SubBoard sub_board = getEmptySubBoard(node->game);
    int nempty = sub_board.pieces.size();

    Board board = node->game;

    TileColour colour_player2;
    if (first_player)
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

    std::shuffle(sub_board.pieces.begin(), sub_board.pieces.end(), rng);
    insertSubBoard(sub_board, board);
    TileColour winner = HexGraph::fullBoardWinner(board);

    return winner;
}
