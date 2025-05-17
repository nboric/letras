//
// Created by Neven Boric on 5/7/25.
//

#include "score.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

void Score::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos) const
{
    sf::Text score(font);
    score.setString("Puntaje: " + std::to_string(score_));
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

void Score::addScore(const int score)
{
    score_ += score;
}
