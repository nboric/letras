//
// Created by Neven Boric on 4/19/25.
//

#ifndef PIECE_H
#define PIECE_H
#include <map>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Tile
{
    static const std::map<std::wstring, int> base_scores_;

    [[nodiscard]] int base_score() const;

    bool is_selected_{ false };
    sf::Rect<float> rect_;

public:
    static constexpr int SIZE{ 50 };
    const std::wstring letter_;
    const int base_score_;

    explicit Tile(std::wstring letter);

    /* TODO: don't really like that I made draw method non const
     * because I store the Rect area to handle clicks later
     * That area is not going to change with every draw, so we should
     * set it somewhere else and get draw method back to const
     */
    void draw(sf::RenderWindow& window, const sf::Font& font,
        sf::Vector2f base_pos);
    void handleClick(sf::Vector2i pos);
    [[nodiscard]] bool isSelected() const;
    void setSelected(bool selected);
};

#endif // PIECE_H
