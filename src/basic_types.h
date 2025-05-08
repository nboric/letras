//
// Created by Neven Boric on 5/7/25.
//

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

using Coord = std::pair<int, int>;

class Placement
{
public:
    Coord coord_;
    std::wstring letter_;
};

#endif //BASIC_TYPES_H
