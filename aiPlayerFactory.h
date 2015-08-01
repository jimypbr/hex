#pragma once

#include <memory>
#include "aiPlayer.h"
#include "pureMonteCarloPlayer.h"
#include "mcSearchTreePlayer.h"

enum class AIPlayerType{RANDOM,PURE_MONTE_CARLO,MC_SEARCH_TREE};

class AIPlayerFactory
{
public:
    static std::unique_ptr<AIPlayer> create(AIPlayerType ptype)
    {
        switch(ptype)
        {
            case AIPlayerType::PURE_MONTE_CARLO:
                return std::unique_ptr<AIPlayer>(new PureMonteCarloPlayer());
            case AIPlayerType::MC_SEARCH_TREE:
                return std::unique_ptr<AIPlayer>(new MCSearchTreePlayer());
        }
    }
};
