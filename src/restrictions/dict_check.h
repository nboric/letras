//
// Created by Neven Boric on 5/4/25.
//

#ifndef DICT_CHECK_H
#define DICT_CHECK_H
#include "restriction.h"

class DictCheck final : public Restriction
{
    static constexpr std::string NAME = "DictCheck";

public:
    bool isValid(Play& play, const Board& board, const Dict& dict, std::string& reason) const override;
    [[nodiscard]] const std::string& getName() const override;
};

#endif //DICT_CHECK_H
