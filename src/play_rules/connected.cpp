//
// Created by Neven Boric on 5/11/25.
//

#include "connected.h"

const std::string& Connected::getName() const
{
    return NAME;
}

bool Connected::isValid(Play& play, const Board& board, std::string& reason) const
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
            Coords coords = buildCoords(play, moving_coord + dir);
            if (board.getTileLetter(coords, letter))
            {
                play.complete_map.emplace(coords, letter);
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
