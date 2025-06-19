//
// Created by nbori on 6/1/2025.
//

#include "gtest/gtest.h"
#include "../src/board.h"
#include "../src/bag.h"

class BoardTest : public testing::Test
{
protected:
    BoardImpl board_;
    // TODO: mock bag
    Bag bag_;

    BoardTest()
    = default;

    [[nodiscard]] std::vector<std::vector<Square> >& getSquares()
    {
        return board_.squares_;
    }

    static int getBorder()
    {
        return BoardImpl::BORDER;
    }

    static int getSize()
    {
        return BoardImpl::SIZE;
    }
};

TEST_F(BoardTest, CanTakeTileInvalid)
{
    EXPECT_FALSE(board_.canTakeTile({getBorder() - 1, getBorder() + 1}));
    EXPECT_FALSE(board_.canTakeTile({getBorder() + 1, getBorder() - 1}));
    EXPECT_FALSE(board_.canTakeTile({getBorder() + getSize()* Tile::SIZE + 1, getBorder() + 1}));
    EXPECT_FALSE(board_.canTakeTile({ getBorder() + 1, getBorder() + getSize()* Tile::SIZE + 1}));
}

TEST_F(BoardTest, CanTakeTileValidOccupied)
{
    auto& squares = getSquares();

    EXPECT_TRUE(board_.canTakeTile({getBorder() + 1, getBorder() + 1}));

    auto tile = bag_.takeOne();
    squares[0][0].place(tile);
    EXPECT_FALSE(board_.canTakeTile({getBorder() + 1, getBorder() + 1}));
}

TEST_F(BoardTest, PlaceTempValid)
{
    auto& squares = getSquares();
    auto tile = bag_.takeOne();
    board_.placeTemp(sf::Vector2i{ getBorder() + 1, getBorder() + 1 }, tile);
    EXPECT_TRUE(squares[0][0].isOccupied());
    EXPECT_TRUE(squares[0][0].isTileTemp());
}

TEST_F(BoardTest, PlaceTempInvalid)
{
    auto& squares = getSquares();
    auto tile = bag_.takeOne();
    board_.placeTemp(sf::Vector2i{ getBorder() + -1, getBorder() + 1 }, tile);
    const auto occupied = std::ranges::find_if(squares, [](auto& square_row)
    {
        return std::find_if(square_row.begin(), square_row.end(), [](auto& square)
        {
            return square.isOccupied();
        }) != square_row.end();
    });
    EXPECT_EQ(occupied, squares.end());
}

TEST_F(BoardTest, GetTileLetterValid)
{
    auto& squares = getSquares();
    auto tile = bag_.takeOne();
    std::wstring letter_pre;
    std::wstring letter_post;
    tile->getLetter(letter_pre);
    squares[0][0].place(tile);
    squares[0][0].setTileTemp(false);
    EXPECT_TRUE(board_.getTileLetter({0, 0}, letter_post));
    EXPECT_EQ(letter_pre, letter_post);
}

TEST_F(BoardTest, GetTileLetterInvalid)
{
    auto& squares = getSquares();
    auto tile = bag_.takeOne();
    std::wstring letter;
    // unoccupied
    EXPECT_FALSE(board_.getTileLetter({0, 0}, letter));

    // invalid coords
    EXPECT_FALSE(board_.getTileLetter({getSize() + 1, 0}, letter));
    EXPECT_FALSE(board_.getTileLetter({0, getSize() + 1}, letter));
    EXPECT_FALSE(board_.getTileLetter({-1, 0}, letter));
    EXPECT_FALSE(board_.getTileLetter({0, -1}, letter));

    // occupied, but temp
    squares[0][0].place(tile);
    EXPECT_FALSE(board_.getTileLetter({0, 0}, letter));
}

TEST_F(BoardTest, GetTileBaseScoreValid)
{
    auto& squares = getSquares();
    auto tile = bag_.takeOne();
    auto score_pre = tile->base_score_;
    int score_post;
    squares[0][0].place(tile);
    EXPECT_TRUE(board_.getTileBaseScore({0, 0}, score_post));
    EXPECT_EQ(score_pre, score_post);
}

TEST_F(BoardTest, GetTileBaseScoreInvalid)
{
    auto tile = bag_.takeOne();
    int score;
    // unoccupied
    EXPECT_FALSE(board_.getTileBaseScore({0, 0}, score));

    // invalid coords
    EXPECT_FALSE(board_.getTileBaseScore({getSize() + 1, 0}, score));
    EXPECT_FALSE(board_.getTileBaseScore({0, getSize() + 1}, score));
    EXPECT_FALSE(board_.getTileBaseScore({-1, 0}, score));
    EXPECT_FALSE(board_.getTileBaseScore({0, -1}, score));
}

TEST_F(BoardTest, GetSquareDefinition)
{
    auto& squares = getSquares();
    const auto definition = board_.getSquareDefinition({ 0, 0 });
    EXPECT_TRUE(definition.has_value());
    EXPECT_EQ(*definition, squares[0][0].definition_);
}
