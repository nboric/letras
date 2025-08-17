//
// Created by nbori on 6/14/2025.
//

#ifndef CPU_PLAYER_H
#define CPU_PLAYER_H
#include "algorithm.h"
#include "../player.h"

class CpuPlayer final : public Player
{
    Algorithm algorithm_;

public:
    explicit CpuPlayer(const std::shared_ptr<Dict>& dict);
    ~CpuPlayer() override = default;
    void draw(sf::RenderWindow& window, const sf::Font& font, bool is_active, sf::Vector2f base_pos) const override;
    void handleClick(sf::Vector2i pos, bool is_exchanging) const override;
    std::unique_ptr<Tile> getSelectedTile() override;
    void unselectAll() const override;
    void exchange(Bag& bag) override;
    [[nodiscard]] Action getAction(const Board& board) const override;
    [[nodiscard]] bool isInteractive() const override;
    void generatePlacements(Board& board) override;
};

#endif //CPU_PLAYER_H
