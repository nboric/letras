//
// Created by Neven Boric on 5/4/25.
//

#include "dict_check.h"

#include <set>
#include <map>
#include <algorithm>
#include <utility>

#include "../dict.h"

const std::string_view& DictCheck::getName() const
{
    return NAME;
}

DictCheck::DictCheck(std::shared_ptr<const Dict> dict)
    : dict_(std::move(dict))
{
}

bool DictCheck::isValid(Play& play, const Board& board, std::optional<std::string>& reason) const
{
    std::string word;
    const int min = *play.moving_coord_values.begin() - 1;
    const int max = *play.moving_coord_values.rbegin() + 1;
    for (int moving_coord = min; moving_coord <= max; moving_coord++)
    {
        Coords coords = buildCoords(play, moving_coord);
        if (play.complete_map.contains(coords))
        {
            auto& letter = play.complete_map.at(coords);
            word.append(letter.begin(), letter.end());
        }
    }
    std::ranges::transform(word, word.begin(),
        [](const unsigned char c) { return std::tolower(c); });
    // TODO: must exclude CH, LL, RR made with two Tiles
    if (!dict_->is_valid(word))
    {
        if (reason)
        {
            *reason = "Word " + word + " not found in dictionary";
        }
        return false;
    }
    return true;
}
