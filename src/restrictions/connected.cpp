//
// Created by Neven Boric on 5/11/25.
//

#include "connected.h"

const std::string& Connected::getName() const
{
    return NAME;
}

bool Connected::isValid(Play& play, const Board& board, const Dict& dict, std::string& reason) const
{
    if (play.is_first)
    {
        return true;
    }
    bool is_connected = false;
    for (auto const& moving_coord : play.moving_coord_values)
    {
        for (const auto dir : { -1, 1 })
        {
            std::wstring letter;
            Coords coord;
            if (play.direction == Play::VERTICAL)
            {
                coord = { moving_coord + dir, play.fixed_coord_value };
            }
            else
            {
                coord = { play.fixed_coord_value, moving_coord + dir };
            }
            if (board.getTileLetter(coord, letter))
            {
                play.complete_map.emplace(coord, letter);
                is_connected = true;
            }
        }
    }
    if (!is_connected)
    {
        reason = "Play doesn't use existing tiles";
    }
    return is_connected;
}
