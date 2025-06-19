//
// Created by nbori on 6/15/2025.
//

#include <algorithm>

#include "../src/cpu/algorithm.h"
#include "gtest/gtest.h"

class AlgorithmTest : public testing::Test
{
protected:
    AlgorithmTest()
        : algorithm_(std::make_shared<Dict>("res/dict/fise-2.txt"))
    {
    }

    Algorithm algorithm_;
};

TEST_F(AlgorithmTest, GetStartPositions)
{
    std::vector<int> starting_positions;
    algorithm_.getStartPositions(starting_positions, 7);
    const auto [min, max] = std::ranges::minmax_element(starting_positions);
    EXPECT_EQ(7, starting_positions.size());
    EXPECT_EQ(*max, 1);
    EXPECT_EQ(*min, -6);
    EXPECT_EQ(std::ranges::find(starting_positions, 0), starting_positions.end());
}

TEST_F(AlgorithmTest, GetCoords)
{
    for (auto direction : { VERTICAL, HORIZONTAL })
    {
        for (const auto starting_position : { -5, -2, -1, 1 })
        {
            for (const auto n_tiles : { 1, 2, 3, 4, 5, 6, 7 })
            {
                if (starting_position + n_tiles < 0)
                {
                    // not enough tiles to start that far back, skip
                    // TODO: function should return error
                    continue;
                }
                SCOPED_TRACE(
                    "direction = " + std::to_string(direction) + ", starting_position = " + std::to_string(
                        starting_position) + ", n_tiles = " + std::to_string(n_tiles));
                std::vector<Coords> coords_list;
                Coords existing_tile_coords{ 10, 10 };
                algorithm_.getCoords(coords_list, direction, existing_tile_coords, starting_position, n_tiles);
                EXPECT_EQ(n_tiles, coords_list.size());
                const auto fixed_coord_doesnt_change = std::ranges::all_of(coords_list, [&](const Coords& coords)
                {
                    if (direction == VERTICAL)
                    {
                        return coords.second == existing_tile_coords.second;
                    }
                    return coords.first == existing_tile_coords.first;
                });
                EXPECT_TRUE(fixed_coord_doesnt_change);
                const int first_pos_delta = starting_position;
                int last_pos_delta;
                if (n_tiles == 1)
                {
                    last_pos_delta = starting_position;
                }
                else
                {
                    last_pos_delta = starting_position + n_tiles;
                    if (starting_position == 1 || starting_position + n_tiles == 0)
                    {
                        last_pos_delta--;
                    }
                }
                if (direction == VERTICAL)
                {
                    EXPECT_EQ(existing_tile_coords.first + first_pos_delta, coords_list[0].first);
                    EXPECT_EQ(existing_tile_coords.first + last_pos_delta, coords_list[n_tiles-1].first);
                }
                else
                {
                    EXPECT_EQ(existing_tile_coords.second + first_pos_delta, coords_list[0].second);
                    EXPECT_EQ(existing_tile_coords.second + last_pos_delta, coords_list[n_tiles-1].second);
                }
            }
        }
    }
}
