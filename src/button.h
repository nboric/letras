//
// Created by Neven Boric on 5/4/25.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Button
{
    sf::Rect<float> rect_;

    bool is_pressed_{ false };

    const std::string text_;

    static constexpr int HEIGHT{ 50 };

public:
    explicit Button(std::string text);
    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos);
    bool handleClick(sf::Vector2i pos);
};

#endif //BUTTON_H
