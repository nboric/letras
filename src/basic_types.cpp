//
// Created by Neven Boric on 8/10/25.
//

#include "basic_types.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Coords& obj)
{
    os << obj.first << ',' << obj.second;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Placement& obj)
{
    os << obj.coords_ << " -> " << obj.letter_;
    return os;
}
