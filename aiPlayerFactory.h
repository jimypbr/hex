#pragma once

#include <memory>
#include "aiPlayer.h"
#include "pureMonteCarloPlayer.h"

enum class AIPlayerType{RANDOM,PURE_MONTE_CARLO,MC_SEARCH_TREE};

class AIPlayerFactory
{
public:
    static std::unique_ptr<AIPlayer> create(AIPlayerType ptype, int s)
    {
        switch(ptype)
        {
            case AIPlayerType::PURE_MONTE_CARLO:
                return std::unique_ptr<AIPlayer>(new PureMonteCarloPlayer(s));
        }
    }
};
