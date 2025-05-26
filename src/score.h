//
// Created by Neven Boric on 5/7/25.
//

#ifndef SCORE_H
#define SCORE_H
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Score
{
    int score_{ 0 };
    static constexpr int HEIGHT{ 50 };

    friend class PlayerTest;

public:
    void addScore(int score);
    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;
};

#endif //SCORE_H
