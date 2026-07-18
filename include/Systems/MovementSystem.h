#pragma once

#include "Core/Player.h"

namespace EvoSphere
{
    int rollEnergyOrbs();

    void movePlayer(Player& player, int rollTotal);

    bool didPassOriginGate(int oldPosition, int newPosition, int rollTotal);

    void applyOriginGateReward(Player& player);
}
