#pragma once

#include "Core/Player.h"

namespace EvoSphere
{
    bool canEvolve(const Player& player, const Evoran& evoran);//this function checks if a player can evolve a specific Evoran. It takes a constant reference to a Player object and a constant reference to an Evoran object as parameters. The function first checks if the player is not defeated using the isDefeated function. Then, it checks if the player has enough evolution gems (at least EVOLUTION_GEM_COST) using the getEvolutionGems function. Finally, it checks if the Evoran can evolve using the canEvolve function. If all three conditions are met, the function returns true, indicating that the player can evolve the specified Evoran; otherwise, it returns false.

    bool evolveSelectedEvoran(Player& player, int evoranIndex);//this function attempts to evolve a selected Evoran for a player. It takes a reference to a Player object and an integer representing the index of the selected Evoran in the player's ownedEvorans vector. The function first checks if the evoranIndex is valid (i.e., within the bounds of the ownedEvorans vector). If the index is invalid, it returns false. Then, it retrieves a reference to the selected Evoran and checks if the player can evolve it using the canEvolve function. If the player cannot evolve the Evoran or if the evolution fails, it returns false. If the evolution is successful, it spends the required evolution gems from the player, updates any penalties related to having no active Evorans, and prints a message indicating that the Evoran has evolved. Finally, it returns true to indicate that the evolution was successful.

    void showEvolutionOptions(const Player& player);//this function displays the evolution options for the player. It takes a constant reference to a Player object as a parameter. The function first prints a header message "Evolution options:". Then, it iterates through the player's owned Evorans using a for loop. For each Evoran, it checks if the Evoran can evolve using the canEvolve function. If the Evoran can evolve, it prints the index of the Evoran, its current name (obtained using getName), and its evolved name (obtained using getEvolvedName) in the format "index. currentName -> evolvedName". This provides the player with a list of Evorans that are eligible for evolution along with their corresponding evolved forms.
}
