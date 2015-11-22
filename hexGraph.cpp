
#include <vector>
#include <queue>
#include <iostream>
#include "hexGraph.h"
#include "board.h"

static inline int coord2index(int row, int col, int side)
{
	return row*side + col;
}


bool HexGraph :: whiteWon(const Board & board)
{
	/*
	 * The board is represented as a graph where the tiles are vertices and
	 * there is an edge between a tile and its neighbours.
	 * 4 virtual nodes are included on the NORTH, SOUTH, EAST, and WEST
	 * of the board. NORTH and SOUTH are always WHITE, while EAST and WEST
	 * are always BLACK.
	 * A path connecting NORTH->SOUTH => white win
	 * A path connecting EAST->WEST => black win
	 */
	int ntiles = board.ntiles();
    int neighbours_size = std::max(6, board.side());
    std::vector<int> neighbours(neighbours_size);
	std::vector<bool> visited(ntiles+4, false);
	std::queue<int> q;

	int north = ntiles;
	int south = ntiles + 1;
	visited[north] = true;
	q.push(north);

	while (!q.empty())
	{
		int s = q.front();
		q.pop();

		//std::vector<int> neighbours = neighbourNodes(s, board.side());
        neighbourNodesFast(s, board.side(), neighbours);
		for (auto n : neighbours)
		{
            if (n < 0)
                continue;

			bool connected;
			if (n < ntiles)
				connected = (board[n] == TileColour::WHITE);
			else
				connected = (n == north) || (n == south);
			if (connected)
			{
				if (!visited[n])
				{
					visited[n] = true;
					q.push(n);
				}
			}
		}
	}

	// if south node is visited then white wins
	return visited[south];
}

bool HexGraph :: blackWon(const Board & board)
{
	/*
	 * The board is represented as a graph where the tiles are vertices and
	 * there is an edge between a tile and its neighbours.
	 * 4 virtual nodes are included on the NORTH, SOUTH, EAST, and WEST
	 * of the board. NORTH and SOUTH are always WHITE, while EAST and WEST
	 * are always BLACK.
	 * A path connecting NORTH->SOUTH => white win
	 * A path connecting WEST->EAST => black win
	 */
	int ntiles = board.ntiles();
    int neighbours_size = std::max(6, board.side());
    std::vector<int> neighbours(neighbours_size);
	std::vector<bool> visited(ntiles+4, false);
	std::queue<int> q;

	int west = ntiles + 2;
	int east = ntiles + 3;
	visited[west] = true;
	q.push(west);

	while (!q.empty())
	{
		int s = q.front();
		q.pop();

		//std::vector<int> neighbours = neighbourNodes(s, board.side());
        neighbourNodesFast(s, board.side(), neighbours);
		for (auto n : neighbours)
		{
            if (n < 0)
                continue;

			bool connected;
			if (n < ntiles)
				connected = (board[n] == TileColour::BLACK);
			else
				connected = (n == west) || (n == east);
			if (connected)
			{
				if (!visited[n])
				{
					visited[n] = true;
					q.push(n);
				}
			}
		}
	}

	// if east node is visited then black wins
	return visited[east];
}

TileColour HexGraph :: fullBoardWinner(const Board & board)
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

void HexGraph::neighbourNodesFast(int t, int side, std::vector<int> &neighbours)
{
	int ntiles = side*side;

    // init neighbours vector to null value
    for (auto& neighbour : neighbours)
        neighbour = -1;

	int nidx = 0;

	// virtual nodes
	if (t == ntiles)
	{
		//north
		for (int tile = 0; tile < side; ++tile)
            neighbours[nidx++] = tile;
	}
	else if (t == ntiles+1)
	{
		//south
		for (int tile = ntiles-side-1; tile < ntiles; ++tile)
			neighbours[nidx++] = tile;
	}
	else if (t == ntiles+2)
	{
		// west
		for (int tile = 0; tile < side*side; tile+=side)
			neighbours[nidx++] = tile;
	}
	else if (t == ntiles+3)
	{
		// east
		for (int tile = side-1; tile < side*side; tile+=side)
			neighbours[nidx++] = tile;
	}
	else
	{
		// real nodes

		// 2d coordinates
		int row = t / side;
		int col = t % side;

		if (row == 0)
		{
			neighbours[nidx++] = ntiles;
			neighbours[nidx++] = coord2index(row+1,col,side);
		}
		else if (row == (side-1))
		{
			neighbours[nidx++] = ntiles + 1;
			neighbours[nidx++] = coord2index(row-1,col,side);
		}
		else
		{
			neighbours[nidx++] = coord2index(row+1,col,side);
			neighbours[nidx++] = coord2index(row-1,col,side);
		}

		if (col == 0)
		{
			neighbours[nidx++] = ntiles+2;
			neighbours[nidx++] = coord2index(row,col+1,side);

			if (row > 0)
				neighbours[nidx++] = coord2index(row-1,col+1,side);
		}
		else if (col == (side-1))
		{
			neighbours[nidx++] = ntiles + 3;
			neighbours[nidx++] = coord2index(row,col-1,side);

			if (row < (side-1))
				neighbours[nidx++] = coord2index(row+1,col-1,side);
		}
		else
		{
			neighbours[nidx++] = coord2index(row,col+1,side);
			neighbours[nidx++] = coord2index(row,col-1,side);

			if (row > 0)
				neighbours[nidx++] = coord2index(row-1,col+1,side);
			if (row < (side-1))
				neighbours[nidx++] = coord2index(row+1,col-1,side);
		}
	}
}

std::vector<int> HexGraph ::neighbourNodes(int t, int side)
{
	int ntiles = side*side;
	std::vector<int> neighbours;

	// virtual nodes
	if (t == ntiles)
	{
		//north
		for (int i = 0; i < side; ++i)
			neighbours.push_back(i);
	}
	else if (t == ntiles+1)
	{
		//south
		for (int i = ntiles-side-1; i < ntiles; ++i)
			neighbours.push_back(i);
	}
	else if (t == ntiles+2)
	{
		// west
		for (int i = 0; i < side*side; i+=side)
			neighbours.push_back(i);
	}
	else if (t == ntiles+3)
	{
		// east
		for (int i = side-1; i < side*side; i+=side)
			neighbours.push_back(i);
	}
	else
	{
		// real nodes

		// 2d coordinates
		int row = t / side;
		int col = t % side;

		if (row == 0)
		{
			neighbours.push_back(ntiles);
			neighbours.push_back(coord2index(row+1,col,side));
		}
		else if (row == (side-1))
		{
			neighbours.push_back(ntiles + 1);
			neighbours.push_back(coord2index(row-1,col,side));
		}
		else
		{
			neighbours.push_back(coord2index(row+1,col,side));
			neighbours.push_back(coord2index(row-1,col,side));
		}

		if (col == 0)
		{
			neighbours.push_back(ntiles+2);
			neighbours.push_back(coord2index(row,col+1,side));

			if (row > 0)
				neighbours.push_back(coord2index(row-1,col+1,side));
		}
		else if (col == (side-1))
		{
			neighbours.push_back(ntiles + 3);
			neighbours.push_back(coord2index(row,col-1,side));

			if (row < (side-1))
				neighbours.push_back(coord2index(row+1,col-1,side));
		}
		else
		{
			neighbours.push_back(coord2index(row,col+1,side));
			neighbours.push_back(coord2index(row,col-1,side));

			if (row > 0)
				neighbours.push_back(coord2index(row-1,col+1,side));
			if (row < (side-1))
				neighbours.push_back(coord2index(row+1,col-1,side));

		}
	}
	return neighbours;
}
