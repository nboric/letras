//
// Created by Neven Boric on 5/4/25.
//

#ifndef CONTIGUOUS_H
#define CONTIGUOUS_H
#include "restriction.h"

class Contiguous final : public Restriction
{
    static constexpr std::string NAME = "Contiguous";

public:
    bool isValid(const std::vector<Placement>& placements, Dict& dict, std::string& reason) const override;
    [[nodiscard]] const std::string& getName() const override;
};

#endif //CONTIGUOUS_H
