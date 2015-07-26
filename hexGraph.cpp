
#include <vector>
#include <iostream>
#include "hexGraph.h"
#include "board.h"

bool HexGraph :: whiteWon(const HexBoard& board) const
{
	int board_side = board.side();
	std::vector<bool> prev_open(board_side);
	std::vector<bool> curr_open(board_side);

	// do first row separately
	for (int col=0; col < board_side; ++col)
	{
		prev_open[col] = (board[col] == TileColour::WHITE);
	}

	// remaining rows
	for (int row=1; row < board_side; ++row)
	{
		for (int col=0; col < board_side-1; ++col)
		{
			// open if current node is white and one of its preceding 
			// nodes are also white
			bool is_open = ( board[row*board_side + col] == TileColour::WHITE ) && \
						   ( prev_open[col] || prev_open[col+1] );
			curr_open[col] = is_open;
		}

		// handle end case separately
		bool is_open = ( board[row*board_side + board_side-1] == TileColour::WHITE ) && \
					   ( prev_open[board_side-1] );
		curr_open[board_side-1] = is_open;

		// check for left->right connection on this row
		for (int col=1; col < board_side; ++col)
		{
			if ( (curr_open[col-1] == true) && !(curr_open[col]) )
				if ( board[row*board_side + col] == TileColour::WHITE)
					curr_open[col] = true;
		}

		if (row != (board_side-1))
			std::swap(prev_open, curr_open);
	}

	bool is_winner = false;
	for (int i=0; i < board_side; ++i)
	{
		if (curr_open[i] == true)
		{
			is_winner = true;
			break;
		}
	}

	return is_winner;
}

bool HexGraph :: blackWon(const HexBoard& board) const
{
	int board_side = board.side();
	std::vector<bool> prev_open(board_side);
	std::vector<bool> curr_open(board_side);

	// do first col separately
	for (int row=0; row < board_side; ++row)
	{
		prev_open[row] = (board[row*board_side] == TileColour::BLACK);
	}

	// remaining rows
	for (int col=1; col < board_side; ++col)
	{
		for (int row=0; row < board_side-1; ++row)
		{
			// open if current node is white and one of its preceding 
			// nodes are also white
			bool is_open = ( board[row*board_side + col] == TileColour::BLACK ) && \
						   ( prev_open[row] || prev_open[row+1] );
			curr_open[row] = is_open;
		}

		// handle end case separately
		bool is_open = ( board[board_side*board_side-1] == TileColour::BLACK ) && \
					   ( prev_open[board_side-1] );
		curr_open[board_side-1] = is_open;

		// check for up->down connection on this column
		for (int row=1; row < board_side; ++row)
		{
			if ( (curr_open[row-1] == true) && !(curr_open[row]) )
				if ( board[row*board_side + col] == TileColour::BLACK)
					curr_open[row] = true;
		}

		if (col != (board_side-1))
			std::swap(prev_open, curr_open);
	}

	bool is_winner = false;
	for (int i=0; i < board_side; ++i)
	{
		if (curr_open[i] == true)
		{
			is_winner = true;
			break;
		}
	}

	return is_winner;
}

TileColour HexGraph :: fullBoardWinner(const HexBoard& board) const
{
	// for special case of a full board only need to evaluate if one of the players won 
	// since they can only have opposite values
	
	// evaluate if whiteWon since it has better memory access pattern than blackWon
	bool white_won = whiteWon(board);

	if (white_won)
		return TileColour::WHITE;
	else
		return TileColour::BLACK;
}
