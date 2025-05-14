//
// Created by Neven Boric on 5/11/25.
//

#include "play_builder.h"

#include "calc_score.h"
#include "connected.h"
#include "contiguous.h"
#include "dict_check.h"
#include "first_move.h"

PlayBuilder::PlayBuilder(const Dict& dict)
{
    rules_.push_back(std::make_unique<Contiguous>());
    rules_.push_back(std::make_unique<FirstMove>());
    rules_.push_back(std::make_unique<Connected>());
    rules_.push_back(std::make_unique<DictCheck>(dict));
    rules_.push_back(std::make_unique<CalcScore>());
}

bool PlayBuilder::build(Play& play, const Board& board, std::string& rule_name, std::string& reason) const
{
    for (const auto& rule : rules_)
    {
        if (!rule->isValid(play, board, reason))
        {
            rule_name = rule->getName();
            return false;
        }
    }
    return true;
}
