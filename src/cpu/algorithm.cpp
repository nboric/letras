//
// Created by nbori on 6/14/2025.
//

#include "algorithm.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

#include "../play_rules/play.h"
#include "../play_rules/play_builder.h"

Algorithm::Algorithm(const std::shared_ptr<Dict>& dict)
    : dict_(dict), play_builder_(dict_)
{
}

std::string_view Algorithm::findBestPlay(Board& board, std::vector<std::unique_ptr<Tile> >& tiles) const
{
    auto total_tiles = tiles.size();
    std::vector<Placement> occupied_tiles;
    board.getOccupied(occupied_tiles);
    std::vector<LetterLowercase> player_letters;
    std::string_view winner{};
    for (const auto& tile : tiles)
    {
        LetterLowercase letter;
        tile->getLetterLowercase(letter);
        player_letters.push_back(letter);
    }

    std::unordered_set<std::string_view> checked_words;

    int n_tried_words{ 0 };
    int n_tried_plays{ 0 };
    int n_valid_plays{ 0 };
    int max_score{ 0 };
    for (const auto& occupied_tile : occupied_tiles)
    {
        auto all_words = dict_->filterContaining(occupied_tile.letter_);
        std::cout << "Occupied tile: " << occupied_tile << std::endl;
        for (const auto direction : { HORIZONTAL, VERTICAL })
        {
            const auto n_available_squares = getMaxAvailableSquaresAround(board, occupied_tile.coords_, direction,
                total_tiles);
            std::cout << "Direction: " << direction << ", max available squares: " << n_available_squares << std::endl;
            unsigned char selection_mask = 1;
            while (selection_mask < (1 << total_tiles))
            {
                int n_used_letters = 0;
                for (auto i = 0; i < Player::MAX_TILES; ++i)
                {
                    if (selection_mask & (1 << i))
                    {
                        ++n_used_letters;
                    }
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
                        int placement_pos = 0;
                        for (auto i = 0; i < Player::MAX_TILES; ++i)
                        {
                            if (selection_mask & (1 << i))
                            {
                                std::unique_ptr<Tile> selected = std::move(tiles[i]);
                                // note we don't erase, we will put it back, and want to keep the same position
                                board.placeTemp(placements[placement_pos].coords_, selected);
                                placement_pos++;
                            }
                        }
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
                        }
                        n_valid_plays++;
                        board.returnPlacements(tiles, placements, selection_mask);
                    }
                }
                selection_mask++;
            }
        }
    }
    std::cout << "Tried " << n_tried_words << " words, winner is \"" << winner << "\" with score " << max_score <<
        std::endl;
    return winner;
}
