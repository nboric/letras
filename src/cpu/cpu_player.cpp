//
// Created by nbori on 6/14/2025.
//

#include "cpu_player.h"

bool CpuPlayer::isInteractive() const
{
    return false;
}

Action CpuPlayer::getAction(const Board& board) const
{
    return NONE;
}
