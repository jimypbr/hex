
#include <iostream>
#include <vector>
#include "mcSearchTreePlayer.h"
#include "board.h"
#include "cli_hex.h"
#include "mcNode.h"

static void printBoard_(HexBoard & board);
static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

std::pair<int, int> MCSearchTreePlayer::nextMove(HexBoard board, const HexGraph &hex_graph) const
{
    const int Niter = 10000;

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
        TileColour winner = trialGame_(newNode, hex_graph);

        for (const auto & node : visited)
            node->updateStats(winner);
    }

    // Select the node that gave the best score
    MCNode* best_node = bestMove_(root.get());

    /* debug
    for (const auto& c : root->children)
    {
        int move = c->move;
        std::cout << "(" << move / board.side()+1 << ", " << move % board.side()+1 << ") -- ";
        std::cout << c->nBlackWins << ", ";
        std::cout << c->nWhiteWins << ", ";
        std::cout << c->nVisits << ", ";
        std::cout << c->nBlackWins /  (double) (c->nVisits) << std::endl;
    }
     */

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
        double score = c->nBlackWins / (double) c->nVisits;
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
    auto ran = std::bind(uniform_double, rng_);

    // select node child with best uctValue. Use small random number
    // to break ties.
    for (auto const& cptr : node->children )
    {
        auto c = cptr.get();
        double uctValue = c->nBlackWins / (c->nVisits + EPSILON_) + \
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
    //const int n = (*node).nActions;
    EmptyTiles next_moves = getEmptyTiles_(node->game);

    const int n = next_moves.coords.size();
    TileColour child_colour = node->colour == TileColour::WHITE ? TileColour::BLACK : TileColour::WHITE;
    for (int i=0; i<n; ++i)
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

TileColour MCSearchTreePlayer::trialGame_(MCNode* node, const HexGraph & hex_graph) const
{
    EmptyTiles empty_tiles = getEmptyTiles_(node->game);
    int nempty = empty_tiles.sub_board.size();
    HexBoard board = node->game;

    // assume white goes first
    int nblack_left = nempty / 2;

    // fill up the empty_tiles with black and white
    for (int i = 0; i < nblack_left; ++i)
    {
        empty_tiles.sub_board[i] = TileColour::BLACK;
    }
    for (int i=nblack_left; i<nempty; ++i)
    {
        empty_tiles.sub_board[i] = TileColour::WHITE;
    }

    std::shuffle(empty_tiles.sub_board.begin(), empty_tiles.sub_board.end(), rng);

    //printBoard_(board);
    insertSubBoard_(empty_tiles, board);

    //printBoard_(board);

    TileColour winner = hex_graph.fullBoardWinner(board);

    /*
    if (winner == TileColour::BLACK)
        std::cout << "black win" << std::endl;
    if (winner == TileColour::WHITE)
        std::cout << "white win" << std::endl;
    if (winner == TileColour::EMPTY)
        std::cout << "wat" << std::endl;
    */
     return winner;
}


EmptyTiles MCSearchTreePlayer::getEmptyTiles_(const HexBoard& board) const
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
    et.coords = coords;
    et.sub_board = sub_board;

    return et;
}

inline void MCSearchTreePlayer :: insertSubBoard_(const EmptyTiles& empty_tiles, HexBoard& board) const
{
    // gather subboard into board
    int nempty = empty_tiles.sub_board.size();

    for (int i=0; i<nempty; ++i)
    {
        const int addr = empty_tiles.coords[i];
        board[addr] = empty_tiles.sub_board[i];
    }
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
