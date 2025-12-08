//
// Created by Neven Boric on 12/7/25.
//

#ifndef LETRAS_NON_OVERLAPPING_H
#define LETRAS_NON_OVERLAPPING_H
#include "play_rule.h"

class NonOverlapping final : public PlayRule
{
    static constexpr std::string_view NAME = "NonOverlapping";

public:
    [[nodiscard]] bool isValid(Play& play, const Board& board, std::optional<std::string>& reason) const override;
    [[nodiscard]] const std::string_view& getName() const override;
};

#endif //LETRAS_NON_OVERLAPPING_H
