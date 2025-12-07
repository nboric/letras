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
    BoardMock board_mock_;

    AlgorithmTest()
        : algorithm_(std::make_shared<Dict>("res/dict/fise-2.txt"))
    {
        EXPECT_CALL(board_mock_, areCoordsValid(testing::_))
            .WillRepeatedly([this](const Coords& coords)
            {
                // std::cout << coords << board_.areCoordsValid(coords) << std::endl;
                return board_.areCoordsValid(coords);
            });
    }

    std::shared_ptr<Dict>& getDict()
    {
        return algorithm_.dict_;
    }

    Algorithm algorithm_;
};

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

    std::string winner{};
    std::vector<Placement> placements;
    unsigned char selection_mask;

    ASSERT_TRUE(algorithm_.findBestPlay(board_, player_tiles, winner, placements,selection_mask));
    ASSERT_THAT(winner, testing::AnyOf("abaderna", "randeaba", "bandeara", "abandera"));
}

TEST_F(AlgorithmTest, GetMaxAvailableSquaresAroundSingleOccupied)
{
    EXPECT_CALL(board_mock_, isSquareFree(Coords{6, 6}))
        .WillRepeatedly([](const Coords& coords)
        {
            return false;
        });
    EXPECT_CALL(board_mock_, isSquareFree(testing::_))
        .WillRepeatedly([this](const Coords& coords)
        {
            return board_.areCoordsValid(coords);
        });
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 6), 6);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 5), 5);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 1), 1);
}

TEST_F(AlgorithmTest, GetMaxAvailableSquaresAroundHorizontalWord)
{
    EXPECT_CALL(board_mock_, isSquareFree(testing::_))
        .WillRepeatedly([this](const Coords& coords)
        {
            if (coords.first == 6)
            {
                if (coords.second >= 5 && coords.second <= 7)
                {
                    return false;
                }
            }
            return board_.areCoordsValid(coords);
        });

    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 7), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 5}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 7}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 5}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 7}, VERTICAL, 7), 7);
}

TEST_F(AlgorithmTest, GetMaxAvailableSquaresAroundHorizontalWordBorder)
{
    EXPECT_CALL(board_mock_, isSquareFree(testing::_))
        .WillRepeatedly([this](const Coords& coords)
        {
            if (coords.first == 0)
            {
                if (coords.second >= 5 && coords.second <= 7)
                {
                    return false;
                }
            }
            return board_.areCoordsValid(coords);
        });

    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 6}, HORIZONTAL, 7), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 6}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 5}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 7}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 6}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 5}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 7}, VERTICAL, 7), 7);
}

TEST_F(AlgorithmTest, GetMaxAvailableSquaresAroundMultipleVerticalWords)
{
    EXPECT_CALL(board_mock_, isSquareFree(testing::_))
        .WillRepeatedly([this](const Coords& coords)
        {
            if (coords.first == 6 || coords.first == 4)
            {
                if (coords.second >= 5 && coords.second <= 7)
                {
                    return false;
                }
            }
            return board_.areCoordsValid(coords);
        });
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {4, 6}, HORIZONTAL, 7), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, HORIZONTAL, 1), 0);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {6, 6}, VERTICAL, 7), 7);
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {4, 6}, VERTICAL, 7), 4);
}

TEST_F(AlgorithmTest, GetMaxAvailableSquaresAroundOtherDirectionOccupied)
{
    EXPECT_CALL(board_mock_, isSquareFree(testing::_))
        .WillRepeatedly([this](const Coords& coords)
        {
            if (coords.first == 0)
            {
                if (coords.second >= 5 && coords.second <= 7)
                {
                    return false;
                }
            }
            if (coords.first == 2)
            {
                if (coords.second == 5 || coords.second == 7)
                {
                    return false;
                }
            }
            return board_.areCoordsValid(coords);
        });
    ASSERT_EQ(Algorithm::getMaxAvailableSquaresAround(board_mock_, {0, 6}, VERTICAL, 7), 0);
}
