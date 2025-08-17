//
// Created by nbori on 6/14/2025.
//

#include "algorithm.h"

#include <algorithm>
#include <iostream>
#include <ranges>

#include "../play_rules/play.h"
#include "../play_rules/play_builder.h"

Algorithm::Algorithm(const std::shared_ptr<Dict>& dict)
    : dict_(dict), play_builder_(dict_)
{
}

bool Algorithm::findBestPlay(Board& board, std::vector<std::unique_ptr<Tile> >& tiles, std::string& winner,
    std::vector<Placement>& winning_placements, unsigned char& winning_selection_mask) const
{
    auto n_player_tiles = tiles.size();
    std::vector<Placement> occupied_tiles;
    board.getOccupied(occupied_tiles);
    std::vector<LetterLowercase> player_letters;
    for (const auto& tile : tiles)
    {
        LetterLowercase letter;
        tile->getLetterLowercase(letter);
        player_letters.push_back(letter);
    }

    int n_tried_words{ 0 };
    int n_tried_plays{ 0 };
    int n_valid_plays{ 0 };
    int max_score{ 0 };
    for (const auto& occupied_tile : occupied_tiles)
    {
        std::cout << "Occupied tile: " << occupied_tile << std::endl;
        auto all_words = dict_->filterContaining(occupied_tile.letter_);
        for (const auto direction : { HORIZONTAL, VERTICAL })
        {
            std::unordered_set<std::string_view> checked_words;

            const auto n_available_squares = getMaxAvailableSquaresAround(board, occupied_tile.coords_, direction,
                n_player_tiles);
            std::cout << "Direction: " << direction << ", max available squares: " << n_available_squares << std::endl;
            if (n_available_squares == 0)
            {
                continue;
            }

            // we want to flip all bits in the mask, so we add up to 2^n_player_tiles,
            // even if it's more than available squares, we discard those below
            for (unsigned char selection_mask = 1; selection_mask < 1 << n_player_tiles; selection_mask++)
            {
                int n_used_letters = 0;
                int n_wildcards = 0;
                for (auto i = 0; i < Player::MAX_TILES; ++i)
                {
                    if (selection_mask & 1 << i)
                    {
                        ++n_used_letters;
                        if (player_letters[i].empty())
                        {
                            ++n_wildcards;
                        }
                    }
                }
                if (n_used_letters > n_available_squares)
                {
                    continue;
                }
                // TODO: we have bugs with single letter plays
                if (n_used_letters == 1)
                {
                    continue;
                }
                // TODO: implement wildcard
                if (n_wildcards > 0)
                {
                    continue;
                }
                for (auto word : all_words | std::views::filter(FilterContainingAll{
                                     occupied_tile.letter_, player_letters, n_used_letters, selection_mask
                                 }))
                {
                    if (checked_words.contains(word))
                    {
                        continue;
                    }
                    checked_words.insert(word);
                    std::cout << "Word: " << word << std::endl;

                    n_tried_words++;
                    for (auto occupied_tile_pos = word.find(occupied_tile.letter_, 0);
                         occupied_tile_pos != std::string::npos;
                         occupied_tile_pos = word.find(occupied_tile.letter_,
                             occupied_tile_pos + 1))
                    {
                        n_tried_plays++;
                        std::cout << "Occupied pos: " << occupied_tile_pos << std::endl;
                        auto placements = generatePlacements(occupied_tile, occupied_tile_pos, word, direction,
                            player_letters, selection_mask);
                        board.placeTemp(tiles, placements, selection_mask);
                        Play play(placements);
                        // purposely empty (can't use std::nullopt since it's const)
                        // TODO: we actually want the reason
                        std::optional<std::string> rule, reason;
                        // Failing in CalcScore because it assumes the tiles are placed in the board
                        if (!play_builder_.build(play, board, rule, reason))
                        {
                            std::cout << "Invalid" << std::endl;
                            continue;
                        }
                        std::cout << "Score: " << play.score << std::endl;
                        if (play.score > max_score)
                        {
                            max_score = play.score;
                            winner = word;
                            winning_selection_mask = selection_mask;
                            // copies all elements
                            winning_placements = placements;
                        }
                        n_valid_plays++;
                        board.returnPlacements(tiles, placements, selection_mask);
                    }
                }
            }
        }
    }
    std::cout << "Tried " << n_tried_words << " words, winner is \"" << winner << "\" with score " << max_score <<
        std::endl;
    return n_valid_plays > 0;
}
