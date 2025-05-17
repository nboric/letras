//
// Created by Neven Boric on 5/4/25.
//

#include "button.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Button::Button(std::string text)
    : text_(std::move(text))
{
}

bool Button::handleClick(const sf::Vector2i pos, const ClickEvent event)
{
    if (rect_.contains(sf::Vector2<float>(pos)))
    {
        is_pressed_ = event == CLICK_START;
        return true;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos, const bool is_selected)
{
    // TODO: make relative to Button SIZE
    sf::Text text(font);
    text.setString(text_);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(base_pos + sf::Vector2f{ 15.f, 10.f });

    sf::RectangleShape shape({ text.getLocalBounds().size.x + 30, HEIGHT });
    shape.setPosition(base_pos);
    if (is_pressed_ || is_selected)
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

    window.draw(shape);
    window.draw(text);
}
