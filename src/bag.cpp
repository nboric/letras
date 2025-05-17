//
// Created by Neven Boric on 4/19/25.
//

#include "bag.h"

#include <random>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

const std::map<std::wstring, int> Bag::initial_quantities_ = {
    { L"", 2 },
    { L"A", 12 },
    { L"B", 2 },
    { L"C", 4 },
    { L"CH", 1 },
    { L"D", 5 },
    { L"E", 12 },
    { L"F", 1 },
    { L"G", 2 },
    { L"H", 2 },
    { L"I", 6 },
    { L"J", 1 },
    { L"L", 4 },
    { L"LL", 1 },
    { L"M", 2 },
    { L"N", 5 },
    { L"Ñ", 1 },
    { L"O", 9 },
    { L"P", 2 },
    { L"Q", 1 },
    { L"R", 5 },
    { L"RR", 1 },
    { L"S", 6 },
    { L"T", 4 },
    { L"U", 5 },
    { L"V", 1 },
    { L"X", 1 },
    { L"Y", 1 },
    { L"Z", 1 },
};

Bag::Bag()
{
    for (const auto& [letter, quantity] : initial_quantities_)
    {
        for (int i = 0; i < quantity; i++)
        {
            tiles_.push_back(std::make_unique<Tile>(letter));
        }
    }
}

std::unique_ptr<Tile> Bag::takeOne()
{
    std::random_device random_device;
    std::mt19937 engine{ random_device() };
    std::uniform_int_distribution<size_t> dist(0, tiles_.size() - 1);
    const size_t pos = dist(engine);
    std::swap(tiles_[pos], tiles_.back());
    auto random_element = std::move(tiles_.back());
    tiles_.pop_back();
    return random_element;
}

void Bag::putBack(std::unique_ptr<Tile>& tile)
{
    tiles_.push_back(std::move(tile));
}

void Bag::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos) const
{
    sf::Text score(font);
    score.setString("Bolsa: " + std::to_string(tiles_.size()));
    score.setFillColor(sf::Color::Black);
    score.setCharacterSize(24);
    score.setPosition(base_pos + sf::Vector2f{ 10.f, 10.f });

    sf::RectangleShape shape({ score.getLocalBounds().size.x + 30, HEIGHT });
    shape.setPosition(base_pos);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);

    window.draw(shape);
    window.draw(score);
}
