//
// Created by nbori on 6/15/2025.
//

#include <algorithm>

#include "mocks.h"
#include "../src/cpu/algorithm.h"
#include "gtest/gtest.h"

class AlgorithmTest : public testing::Test
{
protected:
    BoardImpl board_;
    AlgorithmTest()
        : algorithm_(std::make_shared<Dict>("res/dict/fise-2.txt"))
    {
    }

    std::shared_ptr<Dict>& getDict()
    {
        return algorithm_.dict_;
    }

    Algorithm algorithm_;
};

TEST_F(AlgorithmTest, GetStartPositions)
{
    std::vector<int> starting_positions;
    Algorithm::getStartPositions(starting_positions, 7);
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
                Algorithm::getCoords(coords_list, direction, existing_tile_coords, starting_position, n_tiles);
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

TEST_F(AlgorithmTest, FilterContainingAll)
{
    const LetterLowercase occupied_letter = "a";
    std::vector<LetterLowercase> player_letters = { "b", "a", "n", "d", "e", "r", "a" };

    // FilterContainingAll uses least signifigcant bits first;
    unsigned char selection_mask_all = 0b1111111;
    unsigned char selection_mask_first_6 = 0b0111111;
    unsigned char selection_mask_first_2 = 0b0000011;
    unsigned char selection_mask_first_1 = 0b0000001;
    unsigned char selection_mask_random_2 = 0b0110000;

    auto all_words = getDict()->filterContaining(occupied_letter);

    FilterContainingAll all_7{ occupied_letter, player_letters, 7, selection_mask_all };
    EXPECT_TRUE(all_7("abandera"));
    EXPECT_FALSE(all_7("bandera"));

    FilterContainingAll first_6{ occupied_letter, player_letters, 6, selection_mask_first_6 };
    EXPECT_TRUE(first_6("bandera"));
    EXPECT_FALSE(first_6("abandera"));

    // bug
    EXPECT_FALSE(all_7("blandea"));

    // bug where we counted the occupied letter
    FilterContainingAll first_2{ occupied_letter, player_letters, 2, selection_mask_first_2 };
    EXPECT_FALSE(first_2("bar"));

    // bug
    FilterContainingAll first_1{ occupied_letter, player_letters, 1, selection_mask_first_1 };
    EXPECT_FALSE(first_2("abaceria"));

    FilterContainingAll random_2{ occupied_letter, player_letters, 2, selection_mask_random_2 };
    EXPECT_TRUE(random_2("era"));

    std::vector<std::string_view> filtered_words;

    std::ranges::copy_if(all_words, std::back_inserter(filtered_words),
        FilterContainingAll{ occupied_letter, player_letters, 7, selection_mask_all });

    ASSERT_GT(filtered_words.size(), 0);

    ASSERT_NE(std::ranges::find(filtered_words, "abandera"), filtered_words.end());

    ASSERT_TRUE(std::ranges::all_of(filtered_words, [](const auto& word)
        {
        return word.size() == 8;
        }));

    ASSERT_TRUE(std::ranges::all_of(filtered_words, [&](const auto& word)
        {
        return std::ranges::all_of(player_letters, [&](const auto& letter)
            {
            return word.find(letter) != std::string_view::npos;
            });
        }));
}

TEST_F(AlgorithmTest, FilterContainingAllBug)
{
    const LetterLowercase occupied_letter = "r";
    std::vector<LetterLowercase> player_letters = { "s", "e", "o", "l", "e", "d", "d" };

    // FilterContainingAll uses least signifigcant bits first;
    unsigned char selection_mask = 18;

    auto all_words = getDict()->filterContaining(occupied_letter);

    FilterContainingAll filter{ occupied_letter, player_letters, 2, selection_mask };
    EXPECT_FALSE(filter("red"));
}

TEST_F(AlgorithmTest, FilterContainingAllWildcard)
{
    const LetterLowercase occupied_letter = "a";
    std::vector<LetterLowercase> player_letters = { "p", "l", "", "a" };
    unsigned char selection_mask_all = 0b0001111;

    auto all_words = getDict()->filterContaining(occupied_letter);

    FilterContainingAll all_4{ occupied_letter, player_letters, 4, selection_mask_all };
    ASSERT_TRUE(all_4("plaza"));
    ASSERT_TRUE(all_4("plana"));
    ASSERT_FALSE(all_4("plena"));
}

TEST_F(AlgorithmTest, FindAvailablePlays)
{
    std::vector<std::unique_ptr<Tile> > player_tiles;
    player_tiles.emplace_back(std::make_unique<Tile>(L"B"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"A"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"N"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"D"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"E"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"R"));
    player_tiles.emplace_back(std::make_unique<Tile>(L"A"));

    auto tile = std::make_unique<Tile>(L"A");
    board_.placeTemp(Coords{ 7, 7 }, tile);
    board_.acceptPlacements();

    std::vector<Placement> placements;
    unsigned char selection_mask;

    ASSERT_EQ(algorithm_.findBestPlay(board_, player_tiles,placements,selection_mask), "abandera");
}
