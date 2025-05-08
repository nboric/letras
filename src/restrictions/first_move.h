//
// Created by Neven Boric on 5/7/25.
//

#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H
#include "restriction.h"

class FirstMove final : public Restriction
{
    static constexpr std::string NAME = "FirstMove";

public:
    bool isValid(Play& play, const Board& board, const Dict& dict,
        std::string& reason) const override;
    [[nodiscard]] const std::string& getName() const override;
};

#endif //FIRST_MOVE_H
