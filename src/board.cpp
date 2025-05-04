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
                squares_[i].push_back(premium_squares_.at({ i, j }));
            }
            else
            {
                squares_[i].emplace_back(Square::EFFECT::NONE, 0);
            }
        }
    }
}

void Board::draw(sf::RenderWindow& window) const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            auto& square = squares_[i][j];
            sf::RectangleShape shape({ Tile::SIZE, Tile::SIZE });
            shape.setPosition({ BORDER + j * Tile::SIZE, BORDER + i * Tile::SIZE });
            sf::Color background;
            switch (square.effect_)
            {
            case Square::EFFECT::NONE:
                background = sf::Color::White;
                break;
            case Square::EFFECT::LETTER_MULTIPLIER:
                if (square.effect_value_ == 2)
                {
                    background = sf::Color{ 124, 199, 232 };
                }
                else
                {
                    background = sf::Color{ 56, 92, 217 };
                }
                break;
            case Square::EFFECT::WORD_MULTIPLIER:
                if (square.effect_value_ == 2)
                {
                    background = sf::Color{ 255, 184, 196 };
                }
                else
                {
                    background = sf::Color{ 169, 31, 31 };
                }

                break;
            }
            shape.setFillColor(background);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.f);
            window.draw(shape);
        }
    }
}

const std::map<std::pair<int, int>, Square> Board::premium_squares_ = {
    { { 0, 0 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },
    { { 0, 3 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 0, 7 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },
    { { 0, 11 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 0, 14 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },

    { { 1, 1 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 1, 5 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 1, 9 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 1, 13 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 2, 2 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 2, 6 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 2, 8 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 2, 12 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 3, 0 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 3, 3 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 3, 7 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 3, 11 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 3, 14 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 4, 4 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 4, 10 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 5, 1 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 5 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 9 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 5, 13 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },

    { { 6, 2 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 6 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 8 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 6, 12 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 7, 0 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },
    { { 7, 3 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 7, 7 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 7, 11 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 7, 14 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },

    { { 8, 2 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 6 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 8 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 8, 12 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 9, 1 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 5 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 9 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 9, 13 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },

    { { 10, 4 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 10, 10 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 11, 0 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 11, 3 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 11, 7 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 11, 11 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 11, 14 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },

    { { 12, 2 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 12, 6 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 12, 8 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 12, 12 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 13, 1 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },
    { { 13, 5 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 13, 9 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 3) },
    { { 13, 13 }, Square(Square::EFFECT::WORD_MULTIPLIER, 2) },

    { { 14, 0 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },
    { { 14, 3 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 14, 7 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },
    { { 14, 11 }, Square(Square::EFFECT::LETTER_MULTIPLIER, 2) },
    { { 14, 14 }, Square(Square::EFFECT::WORD_MULTIPLIER, 3) },

};
