//
// Created by Neven Boric on 5/17/25.
//

#ifndef WILDCARD_PICKER_H
#define WILDCARD_PICKER_H

#include "basic_types.h"
#include "tile.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class WildcardPicker
{
    std::vector<std::unique_ptr<Tile> > tiles_;

    static constexpr int GRID_SIZE = 6;

public:
    WildcardPicker();
    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;
    std::optional<std::wstring> handleClick(sf::Vector2i pos, ClickEvent event) const;
};

#endif //WILDCARD_PICKER_H
