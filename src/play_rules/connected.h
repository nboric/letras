//
// Created by Neven Boric on 5/11/25.
//

#ifndef CONNECTED_H
#define CONNECTED_H
#include "play_rule.h"

class Connected final : public PlayRule
{
    static constexpr std::string NAME = "Connected";

public:
    [[nodiscard]] bool isValid(Play& play, const Board& board, const Dict& dict, std::string& reason) const override;
    [[nodiscard]] const std::string& getName() const override;
};

#endif //CONNECTED_H
