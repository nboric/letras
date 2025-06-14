//
// Created by nbori on 6/14/2025.
//

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.h"

class HumanPlayer final : public Player
{
     friend class PlayerTest;

public:
     HumanPlayer() = default;
     ~HumanPlayer() override = default;
     void draw(sf::RenderWindow& window, const sf::Font& font, bool is_active, sf::Vector2f base_pos) const override;
     void handleClick(sf::Vector2i pos, bool is_exchanging) const override;
     std::unique_ptr<Tile> getSelectedTile() override;
     void unselectAll() const override;
     void exchange(Bag& bag) override;
     [[nodiscard]] bool isInteractive() const override;
};

#endif //HUMAN_PLAYER_H
