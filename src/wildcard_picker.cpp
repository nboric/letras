//
// Created by Neven Boric on 5/17/25.
//

#include <ranges>

#include "wildcard_picker.h"

#include "bag.h"

WildcardPicker::WildcardPicker()
{
    for (const auto& letter : std::views::keys(Bag::initial_quantities_))
    {
        if (!letter.empty())
        {
            tiles_.push_back(std::make_unique<Tile>(letter));
        }
    }
}

void WildcardPicker::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos) const
{
    for (int i = 0; i < tiles_.size(); i++)
    {
        tiles_[i]->draw(window, font, base_pos + sf::Vector2f{
                                          static_cast<float>(i % GRID_SIZE * Tile::SIZE),
                                          static_cast<float>(i / GRID_SIZE * Tile::SIZE)
                                      }, false);
    }
}

std::optional<std::wstring> WildcardPicker::handleClick(const sf::Vector2i pos, const ClickEvent event) const
{
    for (const auto& tile : tiles_)
    {
        if (tile->handleClick(pos, event))
        {
            return tile->letter_;
        }
    }
    return std::nullopt;
}
