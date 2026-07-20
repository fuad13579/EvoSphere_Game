#include "Systems/EvolutionSystem.h"

#include <iostream>

namespace EvoSphere
{
    bool canEvolve(const Player& player, const Evoran& evoran)
    {
        return !isDefeated(&player) &&
            getEvolutionGems(&player) >= EVOLUTION_GEM_COST &&
            canEvolve(&evoran);
    }// This function checks if a player can evolve a specific Evoran. It takes a constant reference to a Player object and a constant reference to an Evoran object as parameters. The function first checks if the player is not defeated using the isDefeated function. Then, it checks if the player has enough evolution gems (at least EVOLUTION_GEM_COST) using the getEvolutionGems function. Finally, it checks if the Evoran can evolve using the canEvolve function. If all three conditions are met, the function returns true, indicating that the player can evolve the specified Evoran; otherwise, it returns false.

    bool evolveSelectedEvoran(Player& player, int evoranIndex)
    {
        if (evoranIndex < 0 ||
            evoranIndex >= static_cast<int>(player.ownedEvorans.size()))//static cast to convert the size of the ownedEvorans vector to an integer. because the size() function returns a value of type size_t, which is an unsigned integer type. By casting it to int, we ensure that the comparison with evoranIndex (which is of type int) is valid and avoids potential issues with signed/unsigned integer comparisons.
        {
            return false;
        }

        Evoran& selectedEvoran = player.ownedEvorans[evoranIndex];

        if (!canEvolve(player, selectedEvoran) ||
            !evolve(&selectedEvoran))
        {
            return false;
        }

        spendEvolutionGems(&player, EVOLUTION_GEM_COST);
        updateNoActiveEvoranPenalty(&player);// update the penalty for not having an active Evoran after the evolution.

        std::cout << getName(&selectedEvoran)
                << " evolved into "
                << getDisplayName(&selectedEvoran)
                << "!\n";

        return true;
    }

    void showEvolutionOptions(const Player& player)// This function displays the evolution options for the player. It takes a constant reference to a Player object as a parameter. The function first prints a header message "Evolution options:". Then, it iterates through the player's owned Evorans using a for loop. For each Evoran, it checks if the Evoran can evolve using the canEvolve function. If the Evoran can evolve, it prints the index of the Evoran, its current name (obtained using getName), and its evolved name (obtained using getEvolvedName) in the format "index. currentName -> evolvedName". This provides the player with a list of Evorans that are eligible for evolution along with their corresponding evolved forms.
    {
        std::cout << "Evolution options:\n";

        for (int i = 0;
            i < static_cast<int>(player.ownedEvorans.size());//static cast to convert the size of the ownedEvorans vector to an integer. because the size() function returns a value of type size_t, which is an unsigned integer type. By casting it to int, we ensure that the comparison with i (which is of type int) is valid and avoids potential issues with signed/unsigned integer comparisons.
            ++i)
        {
            const Evoran& evoran = player.ownedEvorans[i];

            if (canEvolve(&evoran))
            {
                std::cout << i
                        << ". "
                        << getName(&evoran)
                        << " -> "
                        << getEvolvedName(&evoran)
                        << "\n";
            }
        }
    }
}
