//
// Created by Neven Boric on 5/13/25.
//

#include <ranges>

#include "calc_score.h"

const std::string_view& CalcScore::getName() const
{
    return NAME;
}

bool CalcScore::isValid(Play& play, const Board& board, std::optional<std::string>& reason) const
{
    int score = 0;
    int word_multiplier = 1;
    // we don't use structured binding in this case, since there's no support for ignoring values
    // views::keys is much better than getting a pair and using .first
    for (auto const& coords : std::views::keys(play.complete_map))
    {
        int tile_score;
        if (!board.getTileBaseScore(coords, tile_score))
        {
            return false;
        }
        auto const& definition = board.getSquareDefinition(coords);
        if (!definition.has_value())
        {
            return false;
        }
        const auto& [effect_, effect_value_] = *definition;

        if (play.placement_map.contains(coords))
        {
            switch (effect_)
            {
            case SquareDefinition::LETTER_MULTIPLIER:
                tile_score *= effect_value_;
                break;
            case SquareDefinition::WORD_MULTIPLIER:
                word_multiplier *= effect_value_;
                break;
            default:
                break;
            }
        }
        score += tile_score;
    }
    score *= word_multiplier;
    play.score = score;
    return true;
}
