//
// Created by Neven Boric on 5/4/25.
//

#include "dict_check.h"

#include <set>
#include <map>

#include "../dict.h"

const std::string& DictCheck::getName() const
{
    return NAME;
}

bool DictCheck::isValid(Play& play, const Board& board, const Dict& dict, std::string& reason) const
{
    std::string word;
    const int min = *play.moving_coord_values.begin() - 1;
    const int max = *play.moving_coord_values.end() + 1;
    for (int moving_coord = min; moving_coord <= max; moving_coord++)
    {
        Coords coord;
        if (play.direction == Play::VERTICAL)
        {
            coord = { moving_coord, play.fixed_coord_value };
        }
        else
        {
            coord = { play.fixed_coord_value, moving_coord };
        }
        if (play.complete_map.contains(coord))
        {
            auto& letter = play.complete_map.at(coord);
            /* letter is wstring only to support displaying Ñ correctly in SFML, we don't allow any other wide chars
             * this also handles adding CH, LL, and RR, since we've always treated as a string of two letters
             */
            word.append(std::string(letter.begin(), letter.end()));
        }
    }
    std::ranges::transform(word, word.begin(),
        [](const unsigned char c) { return std::tolower(c); });
    // TODO: must exclude CH, LL, RR made with two Tiles
    if (!dict.is_valid(word))
    {
        reason = "Word " + word + " not found in dictionary";
        return false;
    }
    return true;
}
