//
// Created by Neven Boric on 5/7/25.
//

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

using Coords = std::pair<int, int>;

class Placement
{
public:
    Coords coord_;
    std::wstring letter_;
};

#endif //BASIC_TYPES_H
