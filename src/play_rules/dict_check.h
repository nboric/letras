//
// Created by Neven Boric on 5/4/25.
//

#ifndef DICT_CHECK_H
#define DICT_CHECK_H
#include "play_rule.h"
#include "../dict.h"

class DictCheck final : public PlayRule
{
    static constexpr std::string_view NAME = "DictCheck";
    std::shared_ptr<const Dict> dict_;

public:
    explicit DictCheck(std::shared_ptr<const Dict> dict);

    bool isValid(Play& play, const Board& board, std::optional<std::string>& reason) const override;
    [[nodiscard]] const std::string_view& getName() const override;
};

#endif //DICT_CHECK_H
