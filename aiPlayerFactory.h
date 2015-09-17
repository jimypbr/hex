#pragma once

#include <memory>
#include "aiPlayer.h"
#include "pureMonteCarloPlayer.h"
#include "mcSearchTreePlayer.h"
#include "board.h"

enum class AIPlayerType{PURE_MONTE_CARLO,MC_SEARCH_TREE};

class AIPlayerFactory
{
public:
    static std::unique_ptr<AIPlayer> create(AIPlayerType ptype)
    {
        switch(ptype)
        {
            case AIPlayerType::PURE_MONTE_CARLO:
                return std::unique_ptr<AIPlayer>(new PureMonteCarloPlayer(TileColour::BLACK, false));
            case AIPlayerType::MC_SEARCH_TREE:
                return std::unique_ptr<AIPlayer>(new MCSearchTreePlayer(TileColour::BLACK, false));
        }
    }
};
