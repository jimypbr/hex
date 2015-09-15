
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "mcSearchTreePlayer.h"
#include "board.h"
#include "subBoard.h"
#include "cli_hex.h"
#include "mcNode.h"


static void printBoard_(HexBoard & board);
static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

std::pair<int, int> MCSearchTreePlayer::nextMove(HexBoard board) const
{
    const int Niter = 1000;

    auto root = std::unique_ptr<MCNode>(new MCNode(board, TileColour::WHITE));

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
            cur = select_(cur);
            visited.push_back(cur);
        }
        // is terminal node?
        if (cur->nEmpty == 0)
            continue;
        expand_(cur);

        MCNode* newNode = select_(cur);
        visited.push_back(newNode);

        for (int i = 0; i < 16; ++i)
        {
            TileColour winner = trialGame_(newNode);

            for (const auto &node : visited)
                node->updateStats(winner);
        }
    }

    // Select the node that gave the best score
    MCNode* best_node = bestMove_(root.get());

    // Return that node's move
    int move = best_node->move;
    return std::pair<int, int>(move / board.side(), move % board.side());
}

MCNode* MCSearchTreePlayer :: bestMove_(MCNode* node) const
{
    double best_score = -1;
    MCNode* best_node = nullptr;
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

MCNode* MCSearchTreePlayer::select_(MCNode* node) const
{
    MCNode* selected = nullptr;
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
        if (ai_colour_ == TileColour::BLACK)
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

MCNode* MCSearchTreePlayer::expand_(MCNode* node) const
{
    SubHexBoard next_moves = getEmptySubHexBoard(node->game);
    const int n = next_moves.coords.size();
    TileColour child_colour = oppositeColour(node->colour);

    for (int i = 0; i < n; ++i)
    {
        node->children.push_back( std::unique_ptr<MCNode>(new MCNode( node->game, child_colour ) ));
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

TileColour MCSearchTreePlayer::trialGame_(MCNode* node) const
{
    SubHexBoard sub_board = getEmptySubHexBoard(node->game);
    int nempty = sub_board.colours.size();

    HexBoard board = node->game;

    // assume white goes first
    int nblack_left = nempty / 2;

    // fill up the empty_tiles with black and white
    for (int i = 0; i < nblack_left; ++i)
    {
        sub_board.colours[i] = TileColour::BLACK;
    }
    for (int i = nblack_left; i < nempty; ++i)
    {
        sub_board.colours[i] = TileColour::WHITE;
    }

    std::shuffle(sub_board.colours.begin(), sub_board.colours.end(), rng);
    insertSubHexBoard(sub_board, board);
    TileColour winner = HexGraph::fullBoardWinner(board);

    return winner;
}

static void printBoard_(HexBoard & board)
{
    int board_side_ = board.side();
    std::cout << "   ";
    for (int col = 0; col < board_side_; ++col)
        std::cout << col+1 << "  ";
    std::cout << std::endl;

    for (int row=0; row < board_side_; ++row)
    {
        std::cout << row+1 << "   ";
        for (int col=0; col < board_side_; ++col)
        {
            TileColour tile = board[row*board_side_+col];
            if (tile == TileColour::WHITE)
                std::cout << "W  ";
            else if (tile == TileColour::BLACK)
                std::cout << "B  ";
            else
                std::cout << "-  ";
        }
        std::cout << " " << row+1 << std::endl;
        std::cout << std::string(row+1,' ');	// indent next row
    }
    std::cout << "    ";
    for (int col = 0; col < board_side_; ++col)
        std::cout << col+1 << "  ";
    std::cout << std::endl;
}
