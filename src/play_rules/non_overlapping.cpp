//
// Created by Neven Boric on 12/7/25.
//

#include "non_overlapping.h"

const std::string_view& NonOverlapping::getName() const
{
    return NAME;
}

bool NonOverlapping::isValid(Play& play, const Board& board, std::optional<std::string>& reason) const
{
    if (play.is_first)
    {
        return true;
    }
    for (auto const& moving_coord : play.moving_coord_values)
    {
        for (const auto dir : { -1, 1 })
        {
            Coords coords;
            if (play.direction == VERTICAL)
            {
                coords = { moving_coord, play.fixed_coord_value + dir };
            }
            else
            {
                coords = { play.fixed_coord_value + dir, moving_coord };
            }

            LetterLowercase letter;
            if (board.getTileLetterLowercase(coords, letter))
            {
                if (reason)
                {
                    *reason = "Overlapping in other direction";
                }
                return false;
            }
        }
    }
    return true;
}
