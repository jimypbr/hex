#pragma once

#include "board.h"
#include "hexGraph.h"
#include "pureMonteCarloPlayer.h"
#include "aiPlayer.h"
#include "aiPlayerFactory.h"

class HexGame
{
	private:
		int side_;
		int ntiles_;
		HexBoard main_board_;
		HexGraph hgraph_;
		std::unique_ptr<AIPlayer> ai_;
		TileColour user_colour_;
		TileColour ai_colour_;

	public:
		HexGame(int s) : side_(s), ntiles_(s*s), main_board_(s), \
						 hgraph_(s), user_colour_(TileColour::WHITE), \
						 ai_colour_(TileColour::BLACK)
        {
            ai_ = AIPlayerFactory::create(AIPlayerType::PURE_MONTE_CARLO, s);
        }
		
		bool move(int x, int y);
		void aiMove();
		bool isFinished() const;
		TileColour winner() const;

		const HexBoard& get_main_board() const
		{
			return main_board_;
		}
};
