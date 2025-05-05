//
// Created by Neven Boric on 5/4/25.
//

#ifndef RESTRICTION_H
#define RESTRICTION_H
#include <vector>

class Dict;
class Placement
{
public:
    std::pair<int, int> coord_;
    std::wstring letter_;
};

class Restriction
{
public:
    virtual ~Restriction() = default;

    /* Note that placements is not guaranteed any order, since we're just now checking for restrictions
     * player could've placed tiles in any invalid positions, so sorting doesn't yet make much sense
     */
    [[nodiscard]] virtual bool isValid(const std::vector<Placement>& placements, Dict& dict, std::string& reason) const
    = 0;
    [[nodiscard]] virtual const std::string& getName() const = 0;
};

#endif //RESTRICTION_H
