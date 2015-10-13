#pragma once

#include <memory>
#include "board.h"
#include "hexGraph.h"
#include "aiPlayer.h"
#include "mcSearchTreePlayer.h"
#include "player.h"
#include "humanPlayerCLI.h"
#include "computerPlayer.h"

class HexGame
{
	private:
        /* The number of tiles on the game board side */
		int side_;

        /* The number of tiles, which is the side_**2 */
		int ntiles_;

        /* The board representing the current state of play. */
		Board main_board_;
		std::unique_ptr<Player> p1_;
		std::unique_ptr<Player> p2_;
		TileColour p1_colour_ = TileColour::WHITE;
		TileColour p2_colour_ = TileColour::BLACK;

	public:
        /**
         * Constructor
         *
         * Creates an instance of HexGame with a board of side s.
         * @param s: size of the side of the Hex board.
         */
		HexGame(int s) : side_(s), ntiles_(s*s), main_board_(s)
        {
			p1_ = std::unique_ptr<Player>(new HumanPlayerCLI(p1_colour_));
            p2_ = std::unique_ptr<Player>(new ComputerPlayer(p2_colour_, AIStrategyEnum::MCTS, true));
        }

        HexGame(int s, std::unique_ptr<Player> p1, std::unique_ptr<Player> p2) : side_(s), ntiles_(s*s), main_board_(s)
        {
            p1_ = std::move(p1);
            p2_ = std::move(p2);
        }

		/**
		 * Player 1 move.
		 */
		void movePlayer1();

        /**
         * Player 2 move.
         */
		void movePlayer2();

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
