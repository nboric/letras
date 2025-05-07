//
// Created by Neven Boric on 4/19/25.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "tile.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

/* Since adding std::unique_ptr<Tile> tile_ to Square, it can no longer
 * have a copy constructor, which is needed to initialize map
 * Board::premium_squares_
 * So we move everything that is copyable into this subclass, and make
 * every Square _have_ a SquareDefinition
 */
class SquareDefinition
{
public:
    const enum EFFECT
    {
        NONE,
        LETTER_MULTIPLIER,
        WORD_MULTIPLIER,
    } effect_;

    const int effect_value_;
};

class Square
{
    std::unique_ptr<Tile> tile_{ nullptr };
    const SquareDefinition definition_;
    bool tile_is_temp_{ false };

public:
    explicit Square(SquareDefinition definition);
    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;
    [[nodiscard]] bool isOccupied() const;
    [[nodiscard]] bool isTileTemp() const;
    void setTileTemp(bool temp);
    bool getLetter(std::wstring& letter) const;
    void place(std::unique_ptr<Tile>& tile);
};

#endif //SQUARE_H
