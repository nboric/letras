//
// Created by Neven Boric on 5/7/25.
//

#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H
#include "play_rule.h"

class FirstMove final : public PlayRule
{
    static constexpr std::string_view NAME = "FirstMove";

public:
    bool isValid(Play& play, const Board& board, std::string& reason) const override;
    [[nodiscard]] const std::string_view& getName() const override;
};

#endif //FIRST_MOVE_H
