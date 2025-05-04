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

public:
    static constexpr float SIZE{50.f};
    const std::wstring letter_;
    const int base_score_;

    explicit Tile(std::wstring letter);

    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;
};

#endif //PIECE_H
