#include "Systems/MovementSystem.h"

#include "Utils/Random.h"

namespace EvoSphere
{
    int rollEnergyOrbs()
    {
        return rollTwoOrbs().total;//this function simulates rolling two energy orbs and returns the total value of the roll. The rollTwoOrbs() function is assumed to return a structure containing the total value of the two rolled orbs, and we access that total to return it from this function.
    }

    void movePlayer(Player& player, int rollTotal)
    {
        if (rollTotal <= 0)//this condition checks if the rollTotal is less than or equal to zero. If it is, the function returns early without making any changes to the player's position. This prevents invalid movement and ensures that only positive roll totals result in player movement.
        {
            return;
        }

        const int oldPosition = player.currentPosition;
        const int newPosition = (oldPosition + rollTotal) % BOARD_SIZE;

        movePlayerTo(&player, newPosition);

        if (didPassOriginGate(oldPosition, newPosition, rollTotal))//this condition checks if the player has passed the Origin Gate during their movement. It calls the didPassOriginGate function, passing in the old position, new position, and roll total. If the function returns true, it means the player has passed the Origin Gate, and the applyOriginGateReward function is called to grant the player the associated rewards.
        {
            applyOriginGateReward(player);//this function is called to apply the rewards associated with passing the Origin Gate. It takes the player object as an argument and grants them the appropriate rewards, such as evolution gems and healing for their avatar.
        }
    }

    bool didPassOriginGate(int oldPosition, int newPosition, int rollTotal)//this function checks if the player has passed the Origin Gate during their movement. It takes the old position, new position, and roll total as parameters. The function first checks if the roll total is less than or equal to zero or if the old position is out of bounds (less than 0 or greater than or equal to BOARD_SIZE). If any of these conditions are true, it returns false, indicating that the player did not pass the Origin Gate. Otherwise, it checks if the sum of the old position and roll total is greater than or equal to BOARD_SIZE (indicating that the player has completed a full lap around the board) or if the new position is equal to ORIGIN_GATE_INDEX (indicating that the player landed on the Origin Gate). If either of these conditions is true, it returns true, indicating that the player has passed the Origin Gate.For example, if the old position is 38, the roll total is 5, and the new position is 3, the function will return true because the player has passed the Origin Gate (38 + 5 = 43, which is greater than BOARD_SIZE). If the old position is 10, the roll total is 2, and the new position is 12, the function will return false because the player did not pass the Origin Gate.
    {
        if (rollTotal <= 0 || oldPosition < 0 || oldPosition >= BOARD_SIZE)//how can old position be negative? the answer is that the old position can be negative if the player has not yet been placed on the board or if there is an error in the game logic that allows for an invalid position. In a well-designed game, the old position should always be within the valid range of 0 to BOARD_SIZE - 1. However, this check is included as a safeguard to prevent unexpected behavior in case of invalid input or game state.
        {
            return false;
        }

        return oldPosition + rollTotal >= BOARD_SIZE || newPosition == ORIGIN_GATE_INDEX;
    }

    void applyOriginGateReward(Player& player)//this function applies the rewards associated with passing the Origin Gate. It takes the player object as an argument and grants them the appropriate rewards, such as evolution gems and healing for their avatar. The function calls the addEvolutionGems function to add a specified amount of evolution gems to the player's total, and it calls the healAvatar function to heal the player's avatar by a specified amount. The specific amounts for evolution gems and healing are defined by the constants EVOLUTION_GEM_REWARD and ORIGIN_GATE_HEAL_AMOUNT, respectively.
    {
        addEvolutionGems(&player, EVOLUTION_GEM_REWARD);
        healAvatar(&player, ORIGIN_GATE_HEAL_AMOUNT);
    }
}
