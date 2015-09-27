#pragma once

#include "board.h"
#include "hexGraph.h"
#include "aiPlayer.h"
#include "mcSearchTreePlayer.h"

class HexGame
{
	private:
        /* The number of tiles on the game board side */
		int side_;

        /* The number of tiles, which is the side_**2 */
		int ntiles_;

        /* The board representing the current state of play. */
		Board main_board_;
		std::unique_ptr<AIPlayer> ai_;
		TileColour user_colour_;
		TileColour ai_colour_;

	public:
        /**
         * Constructor
         *
         * Creates an instance of HexGame with a board of side s.
         * @param s: size of the side of the Hex board.
         */
		HexGame(int s) : side_(s), ntiles_(s*s), main_board_(s), \
						 user_colour_(TileColour::WHITE), \
						 ai_colour_(TileColour::BLACK)
        {
			ai_ = std::unique_ptr<AIPlayer>(new MCSearchTreePlayer(ai_colour_, false));
        }

		/**
		 * Attempt to place human piece at board position (x,y).
		 *
		 * out: bool -- true if move is valid, else false.
		 * */
		bool move(int x, int y);

        /**
         * AI decides its next move and places its piece on the board.
         */
		void aiMove();

        /**
         * @return True if the game has a winner, else false.
         */
		bool isFinished() const;

        /**
         * @return The colour of the winning player. If there is no
         * winner returns TileColour::Empty
         */
		TileColour winner() const;

        /**
         * Getter for the Board object in this game object.
         *
         * @return Reference of Board stored in this.
         */
		const Board& get_main_board() const
		{
			return main_board_;
		}
};
