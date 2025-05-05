//
// Created by Neven Boric on 4/19/25.
//

#include "square.h"

#include "tile.h"
#include "SFML/Graphics/RectangleShape.hpp"

Square::Square(const SquareDefinition definition)
    : definition_(definition)
{
}

void Square::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos) const
{
    sf::RectangleShape shape({ Tile::SIZE, Tile::SIZE });
    shape.setPosition(base_pos);
    sf::Color background;
    switch (definition_.effect_)
    {
    case SquareDefinition::NONE:
        background = sf::Color::White;
        break;
    case SquareDefinition::LETTER_MULTIPLIER:
        if (definition_.effect_value_ == 2)
        {
            background = sf::Color{ 124, 199, 232 };
        }
        else
        {
            background = sf::Color{ 56, 92, 217 };
        }
        break;
    case SquareDefinition::WORD_MULTIPLIER:
        if (definition_.effect_value_ == 2)
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

    if (tile_ != nullptr)
    {
        tile_->draw(window, font, base_pos);
    }
}

bool Square::isOccupied() const
{
    return tile_ != nullptr;
}

bool Square::isTileTemp() const
{
    return tile_ != nullptr && tile_is_temp_;
}

bool Square::getLetter(std::wstring& letter) const
{
    if (tile_ != nullptr)
    {
        // a copy
        letter = tile_->letter_;
        return true;
    }
    return false;
}

void Square::place(std::unique_ptr<Tile>& tile)
{
    tile_ = std::move(tile);
    tile_is_temp_ = true;
}
