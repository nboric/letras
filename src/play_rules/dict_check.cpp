//
// Created by Neven Boric on 5/4/25.
//

#include "dict_check.h"

#include <set>
#include <map>
#include <algorithm>

#include "../dict.h"

const std::string_view& DictCheck::getName() const
{
    return NAME;
}

DictCheck::DictCheck(std::shared_ptr<const Dict> dict)
    : dict_(dict)
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
            /* letter is wstring only to support displaying Ñ correctly in SFML, we don't allow any other wide chars
             * this also handles adding CH, LL, and RR, since we've always treated as a string of two letters
             * Although still need special handling since tolower below is not working for Ñ
             */
            if (letter == L"Ñ")
            {
                word.append("ñ");
            }
            else
            {
                word.append(std::string(letter.begin(), letter.end()));
            }
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
