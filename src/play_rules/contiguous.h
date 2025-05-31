//
// Created by Neven Boric on 5/4/25.
//

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H
#include "play_rule.h"

class Contiguous final : public PlayRule
{
    static constexpr std::string_view NAME = "Contiguous";

public:
    bool isValid(Play& play, const Board& board, std::string& reason) const override;
    [[nodiscard]] const std::string_view& getName() const override;
};

#endif //CONTIGUOUS_H
