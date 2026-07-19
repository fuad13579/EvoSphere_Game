#include "Systems/BattleSystem.h"

namespace EvoSphere
{
    void attack(Evoran& attacker, Evoran& defender)// this function simulates an attack from one Evoran to another. It takes references to the attacker and defender Evorans as parameters. The function first checks if either the attacker or defender is defeated (i.e., has 0 or less HP). If either is defeated, the function returns early without performing any attack. If both Evorans are still active, the function calculates the damage dealt by the attacker and applies it to the defender's current HP using the takeDamage function.
    {
        if (isDefeated(&attacker) || isDefeated(&defender))
        {
            return;
        }

        takeDamage(&defender, getDamage(&attacker));//this line calls the takeDamage function, passing in a pointer to the defender Evoran and the damage value obtained from the getDamage function for the attacker Evoran. The takeDamage function reduces the defender's current HP by the specified damage amount, simulating the effect of the attack.
    }

    bool runWildBattle(
        Player& player,
        Evoran& selectedEvoran,
        Evoran& wildEvoran
    )// This function simulates a battle between a player's selected Evoran and a wild Evoran. It takes references to the player, the  selected Evoran, and the wild Evoran as parameters. The function first checks if the player's selected Evoran, or wild Evoran is defeated. If any of them are defeated, the function returns false, indicating that the battle cannot proceed. If all participants are active, the function enters a loop where the selected Evoran attacks the wild Evoran, and then the wild Evoran attacks back. The loop continues until either the selected Evoran or the wild Evoran is defeated. If the wild Evoran's current HP drops below a certain threshold (defined by CAPTURE_HP_THRESHOLD_PERCENT), the function returns true, indicating that the player has a chance to capture the wild Evoran. If the selected Evoran is defeated first, the function returns false.
    {
        if (isDefeated(&player) ||
            isDefeated(&selectedEvoran) ||
            isDefeated(&wildEvoran))
        {
            return false;
        }

        while (!isDefeated(&selectedEvoran) &&
            !isDefeated(&wildEvoran))
        {
            attack(selectedEvoran, wildEvoran);

            if (getCurrentHp(&wildEvoran) * 100 <=
                getMaxHp(&wildEvoran) * CAPTURE_HP_THRESHOLD_PERCENT)
            {
                return true;
            }

            attack(wildEvoran, selectedEvoran);
        }

        updateNoActiveEvoranPenalty(&player);

        return false;
    }

    int calculatePower(const Evoran& evoran)
    {
        return getCurrentHp(&evoran) + getDamage(&evoran);
    }

    void resolveOpponentTileDamage(
        Player& currentPlayer,
        const Evoran& defendingEvoran
    )
    {
        if (isDefeated(&defendingEvoran))
        {
            return;
        }

        takeAvatarDamage(&currentPlayer, getDamage(&defendingEvoran));//this line calls the takeAvatarDamage function, passing in a pointer to the currentPlayer and the damage value obtained from the getDamage function for the defendingEvoran. The takeAvatarDamage function reduces the current player's avatar points by the specified damage amount, simulating the effect of the defending Evoran's attack on the player's avatar.
        
    }
}
