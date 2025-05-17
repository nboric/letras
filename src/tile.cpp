//
// Created by Neven Boric on 4/19/25.
//
#include "tile.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

const std::map<std::wstring, int> Tile::base_scores_ = {
    { L"", 0 },
    { L"A", 1 },
    { L"B", 3 },
    { L"C", 3 },
    { L"CH", 5 },
    { L"D", 2 },
    { L"E", 1 },
    { L"F", 4 },
    { L"G", 2 },
    { L"H", 4 },
    { L"I", 1 },
    { L"J", 8 },
    { L"L", 1 },
    { L"LL", 8 },
    { L"M", 3 },
    { L"N", 1 },
    { L"Ñ", 8 },
    { L"O", 1 },
    { L"P", 3 },
    { L"Q", 5 },
    { L"R", 1 },
    { L"RR", 8 },
    { L"S", 1 },
    { L"T", 1 },
    { L"U", 1 },
    { L"V", 4 },
    { L"X", 8 },
    { L"Y", 4 },
    { L"Z", 10 },
};

Tile::Tile(std::wstring letter)
    : letter_(std::move(letter)),
      base_score_(base_score())
{
}

void Tile::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos, const bool show_score)
{
    sf::RectangleShape shape({ SIZE, SIZE });
    shape.setPosition(base_pos);
    if (is_selected_)
    {
        shape.setFillColor(sf::Color::Yellow);
    }
    else
    {
        shape.setFillColor(sf::Color::White);
    }
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);

    rect_ = shape.getGlobalBounds();

    // TODO: make relative to Tile SIZE
    sf::Text letter(font);
    if (isWildcard() && !assumed_letter_.empty())
    {
        letter.setString(assumed_letter_);
        letter.setFillColor(sf::Color::Blue);
    }
    else
    {
        letter.setString(letter_);
        letter.setFillColor(sf::Color::Black);
    }
    letter.setCharacterSize(24);
    letter.setPosition(base_pos + sf::Vector2f{ 15.f, 10.f });

    window.draw(shape);
    window.draw(letter);

    if (show_score)
    {
        sf::Text score(font);
        score.setString(std::to_wstring(base_score_));
        score.setFillColor(sf::Color::Black);
        score.setCharacterSize(16);
        score.setPosition(base_pos + sf::Vector2f{ 35.f, 30.f });
        window.draw(score);
    }
}

int Tile::base_score() const
{
    // [] operator modifies map if key is not found
    // therefore can't be used inside const function
    return base_scores_.at(letter_);
}

bool Tile::handleClick(const sf::Vector2i pos, const bool allow_multiple)
{
    if (rect_.contains(sf::Vector2<float>(pos)))
    {
        is_selected_ = !is_selected_;
        return true;
    }
    if (!allow_multiple)
    {
        is_selected_ = false;
    }
    return false;
}

bool Tile::isSelected() const
{
    return is_selected_;
}

void Tile::setSelected(const bool selected)
{
    is_selected_ = selected;
}

bool Tile::isWildcard() const
{
    return letter_.empty();
}

void Tile::getLetter(std::wstring& letter) const
{
    if (isWildcard() && !assumed_letter_.empty())
    {
        letter = assumed_letter_;
    }
    else
    {
        letter = letter_;
    }
}

void Tile::setAssumedLetter(const std::wstring& letter)
{
    if (!isWildcard())
    {
        return;
    }
    assumed_letter_ = letter;
}
