//
// Created by Neven Boric on 5/16/25.
//

#include "mocks.h"
#include "../src/board.h"
#include "../src/play_rules/play.h"
#include "../src/play_rules/contiguous.h"
#include "../src/play_rules/first_move.h"
#include "../src/play_rules/connected.h"
#include "../src/play_rules/dict_check.h"
#include "gtest/gtest.h"

class PlayRulesTest : public testing::Test
{
protected:
    BoardMock board_;
    std::optional<std::string> reason_{""};

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

    EXPECT_EQ(play.direction, HORIZONTAL);
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

    EXPECT_EQ(play.direction, VERTICAL);
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

TEST_F(PlayRulesTest, FirstMoveCenterValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 7, 6 }, L"H"));
            placements.push_back(Placement({ 7, 7 }, L"O"));
            placements.push_back(Placement({ 7, 8 }, L"L"));
            placements.push_back(Placement({ 7, 9 }, L"A"));
        });

    EXPECT_CALL(board_, isSquareFree(BoardImpl::center_coords_))
        .Times(1)
        .WillOnce(testing::Return(true));

    Play play(board_);
    FirstMove first_move;

    EXPECT_TRUE(first_move.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, FirstMoveNotCenterValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    EXPECT_CALL(board_, isSquareFree(BoardImpl::center_coords_))
        .Times(1)
        .WillOnce(testing::Return(false));

    Play play(board_);
    FirstMove first_move;

    EXPECT_TRUE(first_move.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, FirstMoveNotCenterInvalid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    EXPECT_CALL(board_, isSquareFree(BoardImpl::center_coords_))
        .Times(1)
        .WillOnce(testing::Return(true));

    Play play(board_);
    FirstMove first_move;

    EXPECT_FALSE(first_move.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ConnectedStartValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 7 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    const Coords coords = { 8, 6 };
    // Order is important here, setting the broader expectation first
    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(board_, getTileLetter(coords, testing::_))
        .Times(1)
        .WillRepeatedly(testing::DoAll(testing::SetArgReferee<1>(L"H"), testing::Return(true)));

    Play play(board_);
    play.is_first = false;
    Connected connected;

    EXPECT_TRUE(connected.isValid(play, board_, reason_));
    EXPECT_TRUE(play.complete_map.contains(coords));
    EXPECT_EQ(play.complete_map.at(coords), L"H");
}

TEST_F(PlayRulesTest, ConnectedEndValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
        });

    const Coords coords = { 8, 9 };
    // Order is important here, setting the broader expectation first
    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(board_, getTileLetter(coords, testing::_))
        .Times(1)
        .WillRepeatedly(testing::DoAll(testing::SetArgReferee<1>(L"A"), testing::Return(true)));

    Play play(board_);
    play.is_first = false;
    Connected connected;

    EXPECT_TRUE(connected.isValid(play, board_, reason_));
    EXPECT_TRUE(play.complete_map.contains(coords));
    EXPECT_EQ(play.complete_map.at(coords), L"A");
}

TEST_F(PlayRulesTest, ConnectedMiddleValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    const Coords coords = { 8, 8 };
    // Order is important here, setting the broader expectation first
    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    // Called twice, once looking forward and another looking back
    EXPECT_CALL(board_, getTileLetter(coords, testing::_))
        .Times(2)
        .WillRepeatedly(testing::DoAll(testing::SetArgReferee<1>(L"L"), testing::Return(true)));

    Play play(board_);
    play.is_first = false;
    Connected connected;

    EXPECT_TRUE(connected.isValid(play, board_, reason_));
    EXPECT_TRUE(play.complete_map.contains(coords));
    EXPECT_EQ(play.complete_map.at(coords), L"L");
}

TEST_F(PlayRulesTest, ConnectedMiddleVerticalValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 6, 8 }, L"H"));
            placements.push_back(Placement({ 7, 8 }, L"O"));
            placements.push_back(Placement({ 9, 8 }, L"A"));
        });

    const Coords coords = { 8, 8 };
    // Order is important here, setting the broader expectation first
    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    // Called twice, once looking forward and another looking back
    EXPECT_CALL(board_, getTileLetter(coords, testing::_))
        .Times(2)
        .WillRepeatedly(testing::DoAll(testing::SetArgReferee<1>(L"L"), testing::Return(true)));

    Play play(board_);
    play.is_first = false;
    Connected connected;

    EXPECT_TRUE(connected.isValid(play, board_, reason_));
    EXPECT_TRUE(play.complete_map.contains(coords));
    EXPECT_EQ(play.complete_map.at(coords), L"L");
}

TEST_F(PlayRulesTest, ConnectedInValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    Play play(board_);
    play.is_first = false;
    Connected connected;

    EXPECT_FALSE(connected.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, ConnectedFirstPlayValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    EXPECT_CALL(board_, getTileLetter(testing::_, testing::_))
        .WillRepeatedly(testing::Return(false));

    Play play(board_);
    play.is_first = true;
    Connected connected;

    EXPECT_TRUE(connected.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, DictCheckSimpleValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 8 }, L"L"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    Play play(board_);
    play.is_first = true;

    // I could (should?) mock Dict, but I actually prefer to check that the word is passed
    // in a format that matches how Dict reads the file
    DictCheck dict_check(std::make_shared<Dict>("res/dict/fise-2.txt"));

    EXPECT_TRUE(dict_check.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, DictCheckSimpleConnectedValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"H"));
            placements.push_back(Placement({ 8, 7 }, L"O"));
            placements.push_back(Placement({ 8, 9 }, L"A"));
        });

    Play play(board_);
    play.is_first = true;

    play.complete_map.emplace(Coords{ 8, 8 }, L"L");

    // I could (should?) mock Dict, but I actually prefer to check that the word is passed
    // in a format that matches how Dict reads the file
    DictCheck dict_check(std::make_shared<Dict>("res/dict/fise-2.txt"));

    EXPECT_TRUE(dict_check.isValid(play, board_, reason_));
}

TEST_F(PlayRulesTest, DictCheckWideValid)
{
    EXPECT_CALL(board_, getPlacements)
        .Times(1)
        .WillOnce([](std::vector<Placement>& placements)
        {
            placements.push_back(Placement({ 8, 6 }, L"N"));
            placements.push_back(Placement({ 8, 7 }, L"I"));
            placements.push_back(Placement({ 8, 8 }, L"Ñ"));
            placements.push_back(Placement({ 8, 9 }, L"O"));
        });

    Play play(board_);
    play.is_first = true;

    // I could (should?) mock Dict, but I actually prefer to check that the word is passed
    // in a format that matches how Dict reads the file
    DictCheck dict_check(std::make_shared<Dict>("res/dict/fise-2.txt"));

    EXPECT_TRUE(dict_check.isValid(play, board_, reason_));
}
