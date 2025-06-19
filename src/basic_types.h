//
// Created by Neven Boric on 5/7/25.
//

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include <utility>
#include <string>

using Coords = std::pair<int, int>;

class Placement
{
public:
    Coords coords_;
    std::wstring letter_;
};

enum ClickEvent
{
    CLICK_START,
    CLICK_END
};

enum Action
{
    NONE,
    PLAY,
    EXCHANGE,
    PASS,
};

enum Direction
{
    VERTICAL,
    HORIZONTAL
};

#endif //BASIC_TYPES_H
