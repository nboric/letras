//
// Created by Neven Boric on 5/16/25.
//

#include "mocks.h"
#include "../src/board.h"
#include "../src/play_rules/play.h"
#include "../src/play_rules/contiguous.h"
#include "gtest/gtest.h"

class PlayRulesTest : public testing::Test
{
protected:
    BoardMock board_;
    std::string reason_;

    PlayRulesTest()
    {
    }
};

TEST_F(PlayRulesTest, BasePlayHorizontalBuild)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 0, 1 }, L"O"));
            placements.push_back(Placement({ 0, 2 }, L"L"));
            placements.push_back(Placement({ 0, 3 }, L"A"));
        });
    Play play(board_);

    EXPECT_EQ(play.direction, Play::HORIZONTAL);
    EXPECT_EQ(play.fixed_coord_value, 0);
    EXPECT_TRUE(play.moving_coord_values.contains(0));
    EXPECT_TRUE(play.moving_coord_values.contains(1));
    EXPECT_TRUE(play.moving_coord_values.contains(2));
    EXPECT_TRUE(play.moving_coord_values.contains(3));
    EXPECT_FALSE(play.moving_coord_values.contains(4));

    EXPECT_EQ(play.all_j, play.moving_coord_values);
    EXPECT_EQ(play.placement_map, play.complete_map);
    EXPECT_TRUE(play.placement_map.contains({0, 1}));
    EXPECT_EQ(play.placement_map.at({0, 1}), L"O");
}

TEST_F(PlayRulesTest, BasePlayVerticalBuild)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 1, 0 }, L"O"));
            placements.push_back(Placement({ 2, 0 }, L"L"));
            placements.push_back(Placement({ 3, 0 }, L"A"));
        });
    Play play(board_);

    EXPECT_EQ(play.direction, Play::VERTICAL);
    EXPECT_EQ(play.fixed_coord_value, 0);
    EXPECT_TRUE(play.moving_coord_values.contains(0));
    EXPECT_TRUE(play.moving_coord_values.contains(1));
    EXPECT_TRUE(play.moving_coord_values.contains(2));
    EXPECT_TRUE(play.moving_coord_values.contains(3));
    EXPECT_FALSE(play.moving_coord_values.contains(4));

    EXPECT_EQ(play.all_i, play.moving_coord_values);
    EXPECT_EQ(play.placement_map, play.complete_map);
    EXPECT_TRUE(play.placement_map.contains({1, 0}));
    EXPECT_EQ(play.placement_map.at({1, 0}), L"O");
}

TEST_F(PlayRulesTest, ContiguousSingleTileValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
        });
    Play play(board_);
    Contiguous contiguous;

    EXPECT_TRUE(contiguous.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ContiguousHorizontalValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 0, 1 }, L"O"));
            placements.push_back(Placement({ 0, 2 }, L"L"));
            placements.push_back(Placement({ 0, 3 }, L"A"));
        });
    Play play(board_);
    Contiguous contiguous;

    EXPECT_TRUE(contiguous.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ContiguousVerticalValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 1, 0 }, L"O"));
            placements.push_back(Placement({ 2, 0 }, L"L"));
            placements.push_back(Placement({ 3, 0 }, L"A"));
        });
    Play play(board_);
    Contiguous contiguous;

    EXPECT_TRUE(contiguous.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ContiguousHorizontalInvalid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 0, 1 }, L"O"));
            placements.push_back(Placement({ 0, 2 }, L"L"));
            placements.push_back(Placement({ 0, 5 }, L"A"));
        });
    EXPECT_CALL(board_, isSquareFree)
        .Times(1)
        .WillOnce(testing::Return(true));

    Play play(board_);
    Contiguous contiguous;

    EXPECT_FALSE(contiguous.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ContiguousVerticalInvalid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 1, 0 }, L"O"));
            placements.push_back(Placement({ 2, 0 }, L"L"));
            placements.push_back(Placement({ 5, 0 }, L"A"));
        });
    EXPECT_CALL(board_, isSquareFree)
        .Times(1)
        .WillOnce(testing::Return(true));

    Play play(board_);
    Contiguous contiguous;

    EXPECT_FALSE(contiguous.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ContiguousAllOverInvalid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 0, 0 }, L"H"));
            placements.push_back(Placement({ 1, 1 }, L"O"));
            placements.push_back(Placement({ 2, 2 }, L"L"));
            placements.push_back(Placement({ 3, 8 }, L"A"));
        });

    Play play(board_);
    Contiguous contiguous;

    EXPECT_FALSE(contiguous.isValid(play, board_, reason_));
}
