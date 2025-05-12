//
// Created by Neven Boric on 5/11/25.
//

#ifndef PLAY_BUILDER_H
#define PLAY_BUILDER_H
#include <vector>

#include "play_rule.h"

class PlayBuilder
{
    std::vector<std::unique_ptr<PlayRule> > rules_;

public:
    PlayBuilder();
    bool build(Play& play, const Board& board, const Dict& dict, std::string& rule_name, std::string& reason) const;
};

#endif //PLAY_BUILDER_H
