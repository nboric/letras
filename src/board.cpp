//
// Created by Neven Boric on 4/19/25.
//

#include "board.h"

#include "square.h"
#include "tile.h"
#include "SFML/Graphics/RectangleShape.hpp"

Board::Board()
{
    squares_.resize(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (premium_squares_.contains({ i, j }))
            {
                squares_[i].emplace_back(premium_squares_.at({ i, j }));
            }
            else
            {
                squares_[i].emplace_back(SquareDefinition(SquareDefinition::EFFECT::NONE, 0));
            }
        }
    }
}

void Board::draw(sf::RenderWindow& window, const sf::Font& font) const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            auto& square = squares_[i][j];
            square.draw(window, font, {
                static_cast<float>(BORDER + j * Tile::SIZE), static_cast<float>(BORDER + i * Tile::SIZE)
            });
        }
    }
}

bool Board::getSquareCoords(const sf::Vector2i pos, Coords& coords)
{
    const int i = (pos.y - BORDER) / Tile::SIZE;
    const int j = (pos.x - BORDER) / Tile::SIZE;

    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
    {
        coords = { i, j };
        return true;
    }
    return false;
}

bool Board::shouldHandleClick(const sf::Vector2i pos) const
{
    Coords coords;
    if (!getSquareCoords(pos, coords))
    {
        return false;
    }
    return !squares_[coords.first][coords.second].isOccupied();
}

bool Board::canTakeTile(const sf::Vector2i pos) const
{
    Coords coords;
    if (!getSquareCoords(pos, coords))
    {
        return false;
    }
    return !squares_[coords.first][coords.second].isOccupied();
}

void Board::placeTemp(const sf::Vector2i pos, std::unique_ptr<Tile>& tile)
{
    Coords coords;
    if (!getSquareCoords(pos, coords))
    {
        return;
    }
    squares_[coords.first][coords.second].place(tile);
}

void Board::getPlacements(std::vector<Placement>& placements) const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (squares_[i][j].isOccupied() && squares_[i][j].isTileTemp())
            {
                std::wstring letter;
                squares_[i][j].getLetter(letter);
                placements.push_back(Placement({ i, j }, letter));
            }
        }
    }
}

void Board::acceptPlacements()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (squares_[i][j].isOccupied() && squares_[i][j].isTileTemp())
            {
                std::wstring letter;
                if (squares_[i][j].isTileTemp())
                {
                    squares_[i][j].setTileTemp(false);
                }
            }
        }
    }
}

bool Board::isSquareFree(const Coords& coords) const
{
    if (coords.first < 0 || coords.first >= SIZE || coords.second < 0 || coords.second >= SIZE)
    {
        return false;
    }
    auto const& square = squares_[coords.first][coords.second];
    return !square.isOccupied() || square.isTileTemp();
}

bool Board::getTileLetter(const Coords& coords, std::wstring& letter) const
{
    if (coords.first < 0 || coords.first >= SIZE || coords.second < 0 || coords.second >= SIZE)
    {
        return false;
    }
    auto const& square = squares_[coords.first][coords.second];
    if (!square.isOccupied() || square.isTileTemp())
    {
        return false;
    }
    return square.getLetter(letter);
}

bool Board::getTileBaseScore(const Coords& coords, int& score) const
{
    if (coords.first < 0 || coords.first >= SIZE || coords.second < 0 || coords.second >= SIZE)
    {
        return false;
    }
    auto const& square = squares_[coords.first][coords.second];
    return square.getTileBaseScore(score);
}

std::optional<const SquareDefinition> Board::getSquareDefinition(const Coords& coords) const
{
    if (coords.first < 0 || coords.first >= SIZE || coords.second < 0 || coords.second >= SIZE)
    {
        // chose signature to return std::optional to handle error case
        // Can't just pass a SquareDefinition by reference as output, as it's const in Square
        // Can't create a copy assignment operator to copy to the output,
        // since fields inside SquareDefinition are const
        return std::nullopt;
    }
    auto const& square = squares_[coords.first][coords.second];
    return square.definition_;
}

const std::map<Coords, SquareDefinition> Board::premium_squares_ = {
    { { 0, 0 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },
    { { 0, 3 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 0, 7 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },
    { { 0, 11 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 0, 14 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },

    { { 1, 1 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 1, 5 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 1, 9 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 1, 13 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 2, 2 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 2, 6 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 2, 8 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 2, 12 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 3, 0 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 3, 3 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 3, 7 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 3, 11 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 3, 14 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 4, 4 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 4, 10 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 5, 1 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 5 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 9 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 13 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },

    { { 6, 2 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 6 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 8 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 12 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 7, 0 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },
    { { 7, 3 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 7, 7 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 7, 11 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 7, 14 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },

    { { 8, 2 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 6 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 8 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 12 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 9, 1 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 5 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 9 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 13 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },

    { { 10, 4 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 10, 10 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 11, 0 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 11, 3 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 11, 7 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 11, 11 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 11, 14 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 12, 2 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 12, 6 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 12, 8 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 12, 12 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 13, 1 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },
    { { 13, 5 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 13, 9 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 13, 13 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 2) },

    { { 14, 0 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },
    { { 14, 3 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 14, 7 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },
    { { 14, 11 }, SquareDefinition(SquareDefinition::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 14, 14 }, SquareDefinition(SquareDefinition::EFFECT::WORD_MULTIPLIER, 3) },

};
