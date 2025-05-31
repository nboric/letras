//
// Created by Neven Boric on 4/19/25.
//

#include "player.h"

Player::Player()
= default;

void Player::replenish(Bag& bag)
{
    const size_t needed = MAX_TILES - tiles_.size();
    if (needed == 0)
    {
        return;
    }
    for (int i = 0; i < needed; i++)
    {
        tiles_.push_back(std::move(bag.takeOne()));
    }
}

void Player::draw(sf::RenderWindow& window, const sf::Font& font, const bool is_active,
    const sf::Vector2f base_pos) const
{
    if (is_active)
    {
        for (int i = 0; i < tiles_.size(); i++)
        {
            tiles_[i]->draw(window, font, base_pos + sf::Vector2f{ static_cast<float>(i * Tile::SIZE), 0 }, true);
        }
    }
    score_.draw(window, font, base_pos + sf::Vector2f{ 0, Tile::SIZE + 10 });
}

void Player::handleClick(const sf::Vector2i pos, const bool is_exchanging) const
{
    for (const auto& tile : tiles_)
    {
        /* TODO: if I make the method void and not stop at the first match
         * we can select two tiles clicking at the border
         */
        tile->handleClick(pos, is_exchanging);
    }
}

std::unique_ptr<Tile> Player::getSelectedTile()
{
    // TODO: don't iterate, save a reference
    for (int i = 0; i < tiles_.size(); i++)
    {
        if (tiles_[i]->isSelected())
        {
            std::unique_ptr<Tile> selected = std::move(tiles_[i]);
            tiles_.erase(tiles_.begin() + i);
            selected->setSelected(false);
            return selected;
        }
    }
    return nullptr;
}

void Player::addScore(const int score)
{
    score_.addScore(score);
}

void Player::takeAll(std::vector<std::unique_ptr<Tile> >& tiles)
{
    while (!tiles.empty())
    {
        tiles_.push_back(std::move(tiles.back()));
        tiles.pop_back();
    }
}

void Player::unselectAll() const
{
    for (const auto& tile : tiles_)
    {
        tile->setSelected(false);
    }
}

void Player::exchange(Bag& bag)
{
    // TODO: check enough available
    std::vector<std::unique_ptr<Tile> > to_exchange;
    for (auto it = tiles_.begin(); it != tiles_.end();)
    {
        if ((*it)->isSelected())
        {
            to_exchange.push_back(std::move(*it));
            // TODO: although this is a small vector, we still can try not to erase from the middle
            it = tiles_.erase(it);
        }
        else
        {
            ++it;
        }
    }
    while (tiles_.size() < MAX_TILES)
    {
        tiles_.push_back(bag.takeOne());
    }
    for (auto& tile : to_exchange)
    {
        bag.putBack(tile);
    }
}
