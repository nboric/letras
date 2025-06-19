//
// Created by nbori on 6/14/2025.
//

#ifndef CPU_PLAYER_H
#define CPU_PLAYER_H
#include "../player.h"

class CpuPlayer : public Player {
public:
    [[nodiscard]] Action getAction(const Board& board) const override;
    [[nodiscard]] bool isInteractive() const override;
};



#endif //CPU_PLAYER_H
