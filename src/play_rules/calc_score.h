//
// Created by Neven Boric on 5/13/25.
//

#ifndef CALC_SCORE_H
#define CALC_SCORE_H
#include "play_rule.h"

class CalcScore final : public PlayRule
{
    static constexpr std::string_view NAME = "CalcScore";

public:
    [[nodiscard]] bool isValid(Play& play, const Board& board, std::optional<std::string>& reason) const override;
    [[nodiscard]] const std::string_view& getName() const override;
};

#endif //CALC_SCORE_H
