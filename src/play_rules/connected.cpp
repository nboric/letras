//
// Created by Neven Boric on 5/11/25.
//

#include "connected.h"

#include <unordered_set>

const std::string_view& Connected::getName() const
{
    return NAME;
}

bool Connected::isValid(Play& play, const Board& board, std::optional<std::string>& reason) const
{
    if (play.is_first)
    {
        return true;
    }
    std::unordered_set<int> connected_coords;
    for (auto const& moving_coord : play.moving_coord_values)
    {
        for (const auto dir : { -1, 1 })
        {
            LetterLowercase letter;
            Coords coords = buildCoords(play, moving_coord + dir);
            if (board.getTileLetterLowercase(coords, letter))
            {
                play.complete_map.emplace(coords, letter);
                connected_coords.emplace(moving_coord + dir);
            }
        }
    }
    if (connected_coords.empty())
    {
        if (reason)
        {
            *reason = "Play doesn't use existing tiles";
        }
        return false;
    }
    if (connected_coords.size() > 1)
    {
        // TODO: is this always a problem?
        if (reason)
        {
            *reason = "Connected to more than one tile";
        }
        return false;
    }
    return true;
}
