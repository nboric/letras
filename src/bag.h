//
// Created by Neven Boric on 4/19/25.
//

#ifndef BAG_H
#define BAG_H
#include <vector>

#include "tile.h"

class Bag
{
    static constexpr int SIZE = 10;
    std::vector<std::unique_ptr<Tile> > tiles_;

    static const std::map<std::wstring, int> initial_quantities_;

public:
    Bag();
    std::unique_ptr<Tile> take_one();
};

#endif //BAG_H
