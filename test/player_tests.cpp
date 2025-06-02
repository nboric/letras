//
// Created by Neven Boric on 5/25/25.
//

#include "../src/player.h"
#include "../src/bag.h"
#include "gtest/gtest.h"

class PlayerTest : public testing::Test
{
protected:
    PlayerTest()
    = default;

    [[nodiscard]] const std::vector<std::unique_ptr<Tile> >& getTiles() const
    {
        return player_.tiles_;
    }

    static int getMaxTiles()
    {
        return Player::MAX_TILES;
    }

    [[nodiscard]] int getScore() const
    {
        return player_.score_.score_;
    }

    void setScore(const int score)
    {
        player_.score_.score_ = score;
    }

    Player player_;
    // TODO: mock bag
    Bag bag_;
};

TEST_F(PlayerTest, Replenish)
{
    auto& tiles = getTiles();
    EXPECT_EQ(tiles.size(), 0);
    player_.replenish(bag_);
    EXPECT_EQ(tiles.size(), getMaxTiles());
}

TEST_F(PlayerTest, TakeAll)
{
    auto& tiles = getTiles();

    const std::array<std::wstring, 4> letters =
    {
        L"H", L"O", L"L", L"A"
    };

    // To check pointer address. We could also just check the letter,
    // but we're also making sure there are no copies
    std::map<std::wstring, Tile*> pointers;
    std::vector<std::unique_ptr<Tile> > new_tiles;
    for (const auto& letter : letters)
    {
        new_tiles.push_back(std::make_unique<Tile>(letter));
        pointers[letter] = new_tiles.back().get();
    }

    player_.takeAll(new_tiles);

    EXPECT_EQ(tiles.size(), 4);
    for (const auto& letter : letters)
    {
        auto t = std::ranges::find_if(tiles, [&](const std::unique_ptr<Tile>& tile)
        {
            return tile->letter_ == letter;
        });
        EXPECT_NE(t, tiles.end());
        EXPECT_EQ(t->get(), pointers[letter]);
    }
}

TEST_F(PlayerTest, Exchange)
{
    auto& tiles = getTiles();
    player_.replenish(bag_);

    std::vector<Tile*> selected;

    for (int i = 0; i < tiles.size(); ++i)
    {
        if (i % 2 == 0)
        {
            tiles[i]->setSelected(true);
            selected.push_back(tiles[i].get());
        }
    }

    player_.exchange(bag_);

    EXPECT_EQ(tiles.size(), getMaxTiles());

    for (auto& pTile : selected)
    {
        auto t = std::ranges::find_if(tiles, [&](const std::unique_ptr<Tile>& tile)
        {
            return tile.get() == pTile;
        });
        EXPECT_EQ(t, tiles.end());
    }
}

TEST_F(PlayerTest, Unselect)
{
    auto& tiles = getTiles();
    player_.replenish(bag_);

    for (int i = 0; i < tiles.size(); ++i)
    {
        if (i % 2 == 0)
        {
            tiles[i]->setSelected(true);
        }
    }
    player_.unselectAll();
    auto t = std::ranges::find_if(tiles, [&](const std::unique_ptr<Tile>& tile)
    {
        return tile->isSelected();
    });
    EXPECT_EQ(t, tiles.end());
}

TEST_F(PlayerTest, AddScore)
{
    setScore(1);
    player_.addScore(10);
    EXPECT_EQ(getScore(), 11);
}

TEST_F(PlayerTest, GetSelectedTile)
{
    auto& tiles = getTiles();
    player_.replenish(bag_);

    Tile* pSelected = tiles[3].get();
    Tile* pNotSelected = tiles[4].get();
    pSelected->setSelected(true);

    auto selected = player_.getSelectedTile();
    EXPECT_EQ(tiles.size(), getMaxTiles() - 1);

    auto t = std::ranges::find_if(tiles, [&](const std::unique_ptr<Tile>& tile)
    {
        return tile.get() == pSelected;
    });
    EXPECT_EQ(t, tiles.end());

    t = std::ranges::find_if(tiles, [&](const std::unique_ptr<Tile>& tile)
    {
        return tile.get() == pNotSelected;
    });
    EXPECT_NE(t, tiles.end());
}
