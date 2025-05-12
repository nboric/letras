//
// Created by Neven Boric on 5/4/25.
//

#ifndef DICT_CHECK_H
#define DICT_CHECK_H
#include "play_rule.h"

class DictCheck final : public PlayRule
{
    static constexpr std::string NAME = "DictCheck";

public:
    bool isValid(Play& play, const Board& board, const Dict& dict, std::string& reason) const override;
    [[nodiscard]] const std::string& getName() const override;
};

#endif //DICT_CHECK_H
