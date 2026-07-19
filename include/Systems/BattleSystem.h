#pragma once

#include "Core/Evoran.h"
#include "Core/Player.h"

namespace EvoSphere
{
    void attack(Evoran& attacker, Evoran& defender);//, this function simulates an attack from one Evoran to another. It takes references to the attacker and defender Evorans as parameters. The function first checks if either the attacker or defender is defeated (i.e., has 0 or less HP). If either is defeated, the function returns early without performing any attack. If both Evorans are still active, the function calculates the damage dealt by the attacker and applies it to the defender's current HP using the takeDamage function.

    bool runWildBattle(
        Player& player,
        Evoran& selectedEvoran,
        Evoran& wildEvoran
    );// This function simulates a battle between a player's selected Evoran and a wild Evoran. It takes references to the player, the selected Evoran, and the wild Evoran as parameters. The function first checks if the player, selected Evoran, or wild Evoran is defeated. If any of them are defeated, the function returns false, indicating that the battle cannot proceed. If all participants are active, the function enters a loop where the selected Evoran attacks the wild Evoran, and then the wild Evoran attacks back. The loop continues until either the selected Evoran or the wild Evoran is defeated. If the wild Evoran's current HP drops below a certain threshold (defined by CAPTURE_HP_THRESHOLD_PERCENT), the function returns true, indicating that the player has a chance to capture the wild Evoran. If the selected Evoran is defeated first, the function returns false.

    int calculatePower(const Evoran& evoran);

    void resolveOpponentTileDamage(
        Player& currentPlayer,
        const Evoran& defendingEvoran
    );
}
