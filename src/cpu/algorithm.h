//
// Created by nbori on 6/14/2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <ranges>

#include "../board.h"
#include "../dict.h"
#include "../player.h"
#include "../play_rules/play_builder.h"

class Algorithm
{
    std::shared_ptr<Dict> dict_;
    const PlayBuilder play_builder_;

    friend class AlgorithmTest;

public:
    explicit Algorithm(const std::shared_ptr<Dict>& dict);
    std::string_view findBestPlay(Board& board, std::vector<std::unique_ptr<Tile> >& tiles, std::vector<Placement>& winning_placements, unsigned char&
        winning_selection_mask) const;

    static void getStartPositions(std::vector<int>& starting_positions, int n_tiles);
    static void getCoords(std::vector<Coords>& coords_list, Direction direction, const Coords& existing_tile_coords,
        int starting_position, int n_tiles);
    static int getMaxAvailableSquaresAround(const Board& board, const Coords& occupied_tile_coords, Direction direction,
        size_t n_player_tiles);

    static std::vector<Placement> generatePlacements(const Placement& occupied_tile, size_t occupied_tile_pos,
        std::string_view word, Direction direction, const std::vector<std::string>& player_letters,
        unsigned char selection_mask);

    static Coords deltaCoords(const Coords& base, int delta, Direction direction);
};

inline Coords Algorithm::deltaCoords(const Coords& base, const int delta, const Direction direction)
{
    if (direction == VERTICAL)
    {
        return { base.first + delta, base.second };
    }
    return { base.first, base.second + delta };
}

inline int Algorithm::getMaxAvailableSquaresAround(const Board& board, const Coords& occupied_tile_coords,
    const Direction direction,
    const size_t n_player_tiles)
{
    // we won't add to existing words, for now
    // TODO: consider consider case when there are more tiles after a space
    for (const auto sign : { -1, 1 })
    {
        Coords coords = deltaCoords(occupied_tile_coords, sign, direction);
        if (!board.isSquareFree(coords))
        {
            return 0;
        }
    }

    int n_available_tiles = 0;
    for (int i = 0; i < n_player_tiles; ++i)
    {
        for (const auto sign : { -1, 1 })
        {
            auto const delta_pos = sign * (i + 1);
            Coords coords = deltaCoords(occupied_tile_coords, delta_pos, direction);
            if (!board.isSquareFree(coords))
            {
                break;
            }
            ++n_available_tiles;
            if (n_available_tiles == n_player_tiles)
            {
                return n_available_tiles;
            }
        }
    }
    return n_available_tiles;
}

inline void Algorithm::getStartPositions(std::vector<int>& starting_positions, const int n_tiles)
{
    for (int start = 1; start > -n_tiles; --start)
    {
        if (start == 0)
        {
            continue;
        }
        starting_positions.push_back(start);
    }
}

inline void Algorithm::getCoords(std::vector<Coords>& coords_list, const Direction direction,
    const Coords& existing_tile_coords,
    const int starting_position,
    const int n_tiles)
{
    for (int pos = 0, i = 0; i < n_tiles; ++i, ++pos)
    {
        if (starting_position + pos == 0)
        {
            pos++;
        }
        auto const delta_pos = starting_position + pos;
        Coords coords = deltaCoords(existing_tile_coords, delta_pos, direction);
        coords_list.push_back(coords);
    }
}

inline std::vector<Placement> Algorithm::generatePlacements(const Placement& occupied_tile,
    const size_t occupied_tile_pos,
    std::string_view word, const Direction direction, const std::vector<std::string>& player_letters,
    const unsigned char selection_mask)
{
    std::vector<Placement> placements;
    std::unordered_set<size_t> used_positions;
    used_positions.insert(occupied_tile_pos);
    for (auto i = 0; i < Player::MAX_TILES; ++i)
    {
        if (selection_mask & (1 << i))
        {
            for (auto pos = word.find(player_letters[i], 0); pos != std::string::npos;
                 pos = word.find(player_letters[i], pos + 1))
            {
                if (used_positions.contains(pos))
                {
                    continue;
                }
                Placement placement;
                placement.letter_ = player_letters[i];
                const int delta_pos = static_cast<int>(pos) - occupied_tile_pos;
                placement.coords_ = deltaCoords(occupied_tile.coords_, delta_pos, direction);
                placements.push_back(placement);
                used_positions.insert(pos);
                break;
            }
        }
    }
    return placements;
}

// Use Functor to pass to std::views::filter for testability
struct FilterContainingAll
{
    const LetterLowercase& occupied_letter;
    std::vector<LetterLowercase>& player_letters_;
    int n_player_letters_;
    unsigned char selection_mask;
    bool operator()(const std::string_view& word) const
    {
        if (word.size() != n_player_letters_ + 1)
        {
            return false;
        }
        int n_wildcards = 0;
        for (auto i = 0; i < Player::MAX_TILES; ++i)
        {
            if (selection_mask & 1 << i)
            {
                // TODO: encapsulate this (maybe get the tiles?)
                if (player_letters_[i].empty())
                {
                    ++n_wildcards;
                }
            }
        }
        std::unordered_set<size_t> used_positions;
        used_positions.insert(word.find(occupied_letter, 0));
        int n_found = 0;
        for (auto i = 0; i < Player::MAX_TILES; ++i)
        {
            if (selection_mask & (1 << i))
            {
                if (player_letters_[i].empty())
                {
                    continue;
                }
                for (auto pos = word.find(player_letters_[i], 0); pos != std::string::npos;
                     pos = word.find(player_letters_[i], pos + 1))
                {
                    if (used_positions.contains(pos))
                    {
                        continue;
                    }
                    n_found++;
                    used_positions.insert(pos);
                    break;
                }
            }
        }
        return n_found + n_wildcards == n_player_letters_;
    }
};

#endif //ALGORITHM_H
