//
// Created by Neven Boric on 5/4/25.
//

#ifndef RESTRICTION_H
#define RESTRICTION_H

#include "../dict.h"
#include "../board.h"
#include "play.h"

class PlayRule
{
public:
    virtual ~PlayRule() = default;

    /* Note that placements is not guaranteed any order, since we're just now checking for restrictions
     * player could've placed tiles in any invalid positions, so sorting doesn't yet make much sense
     */
    [[nodiscard]] virtual bool isValid(Play& play, const Board& board, std::string& reason) const = 0;
    [[nodiscard]] virtual const std::string& getName() const = 0;
};

#endif //RESTRICTION_H
