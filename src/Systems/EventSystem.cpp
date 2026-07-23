#include "Systems/EventSystem.h"

#include <array>

#include "Utils/Random.h"

namespace EvoSphere
{
    namespace
    {
        const std::array<ElementType, 8> EVENT_ELEMENTS{
            ElementType::Fire,
            ElementType::Water,
            ElementType::Nature,
            ElementType::Electric,
            ElementType::Rock,
            ElementType::Air,
            ElementType::Dark,
            ElementType::Mystic
        };// this array contains the different element types that can be selected for events in the game. It is used to randomly choose an element type when resolving events such as blessing shrines or chaos rifts.

        ElementType chooseRandomElement()
        {
            return EVENT_ELEMENTS[randomIndex(
                static_cast<int>(EVENT_ELEMENTS.size())
            )];
        }// this function randomly selects an element type from the EVENT_ELEMENTS array. It uses the randomIndex function to generate a random index within the bounds of the array size, and then returns the corresponding element type. This function is used when resolving events that require selecting a random element type, such as blessing shrines or chaos rifts.
    }//namespace is used to encapsulate the chooseRandomElement function and the EVENT_ELEMENTS array, limiting their scope to this translation unit and preventing name conflicts with other parts of the program.


    bool ownsFullTerritory(
        const Player& player,
        const Board& board,
        ElementType element
    )//this function checks if a player owns the full territory of a specific element type on the game board. It takes a reference to the player, the game board, and the element type as parameters. The function iterates through all tiles on the board and counts how many tiles of the specified element type are owned by the player. If the count matches the total number of tiles of that element type on the board, it returns true, indicating that the player owns the full territory. Otherwise, it returns false.
    {
        if (element == ElementType::None)

        {
            return false;
        }// this line checks if the provided element type is None. If it is, the function returns false, indicating that a player cannot own a full territory of a non-existent element type.

        bool foundTerritoryTile = false;// this line initializes a boolean variable foundTerritoryTile to false. It will be used to track whether any tiles of the specified element type are found on the board.

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            const Tile& tile = board.tiles[i];

            if (tile.tileType != TileType::WildEvoran || tile.elementType != element)
            {
                continue;// this line checks if the current tile is not of type WildEvoran or if its element type does not match the specified element. If either condition is true, the loop continues to the next iteration, skipping the rest of the code for this tile.
            }

            foundTerritoryTile = true;// this line sets foundTerritoryTile to true, indicating that at least one tile of the specified element type has been found on the board.

            if (tile.ownerId != player.playerId)
            {
                return false;
            }// this line checks if the owner of the current tile is not the same as the player's ID. If they are not the same, the function returns false, indicating that the player does not own any tiles of the specified element type on the board.
        }

        return foundTerritoryTile;
    }

    bool applyTerritoryBlessing(
        Player& player,
        Board& board,
        ElementType element
    )
    {
        if (!ownsFullTerritory(player, board, element))
        {
            return false;
        }

        for (Evoran& evoran : player.ownedEvorans)
        {
            if (getElementType(&evoran) == element)// this line checks if the element type of the current Evoran matches the specified element type. If it does, the following code block is executed to apply the blessing effect to that Evoran.
            {
                heal(&evoran, 10);
            }
        }

        updateNoActiveEvoranPenalty(&player);
        return true;
    }

    bool applyTerritoryCurse(
        Player& player,
        Board& board,
        ElementType element
    )
    {
        if (!ownsFullTerritory(player, board, element))
        {
            return false;
        }

        for (Evoran& evoran : player.ownedEvorans)
        {
            if (getElementType(&evoran) == element)
            {
                takeDamage(&evoran, 10);// this line applies the curse effect to the current Evoran by calling the takeDamage function, which reduces the Evoran's current HP by 10. This simulates the negative impact of the territory curse on the Evoran's health.
            }
        }

        updateNoActiveEvoranPenalty(&player);
        return true;
    }

    EventResult resolveBlessingShrine(Player& player, Board& board)
    {
        EventResult result;// this line declares a variable named result of type EventResult, which will be used to store the result of the event.
        result.isBlessing = true;// this line sets the isBlessing field of the result variable to true, indicating that the event is a blessing event.

        if (isDefeated(&player))
        {
            return result;
        }

        result.isMovementEvent = randomIndex(2) == 1;// this line randomly determines whether the event will be a movement event or not. It generates a random index between 0 and 1 (inclusive) using the randomIndex function. If the generated index is 1, it sets result.isMovementEvent to true, indicating that the event will affect the player's movement. If the index is 0, it sets result.isMovementEvent to false, indicating that the event will not affect movement and will instead apply a blessing effect based on the player's territory ownership.

        if (result.isMovementEvent)
        {
            result.movementAmount = randomInt(1, 12);
            movePlayerTo(
                &player,
                player.currentPosition + result.movementAmount
            );// this line calls the movePlayerTo function to move the player forward on the game board by the amount specified in result.movementAmount. It adds the movement amount to the player's current position, effectively moving the player forward by a random number of spaces between 1 and 12 (inclusive). This simulates the positive effect of the blessing event on the player's movement.
            result.applied = true;
            return result;
        }

        result.selectedElement = chooseRandomElement();// this line calls the chooseRandomElement function to randomly select an element type from the predefined EVENT_ELEMENTS array. The selected element type is then assigned to result.selectedElement, which will be used later to determine which territory blessing effect to apply to the player based on their ownership of that element's territory.
        result.applied = applyTerritoryBlessing(
            player,
            board,
            result.selectedElement
        );// this line calls the applyTerritoryBlessing function to apply the blessing effect to the player based on their ownership of the territory associated with the randomly selected element type. It passes the player, board, and result.selectedElement as arguments. The function checks if the player owns the full territory of the specified element type and applies the blessing effect accordingly. The result of this operation (true if the blessing was successfully applied, false otherwise) is assigned to result.applied.

        return result;
    }

    EventResult resolveChaosRift(Player& player, Board& board)
    {
        EventResult result;

        if (isDefeated(&player))
        {
            return result;
        }

        result.isMovementEvent = randomIndex(2) == 1;

        if (result.isMovementEvent)
        {
            result.movementAmount = randomInt(1, 12);
            movePlayerTo(
                &player,
                player.currentPosition - result.movementAmount
            );
            result.applied = true;
            return result;
        }

        result.selectedElement = chooseRandomElement();
        result.applied = applyTerritoryCurse(
            player,
            board,
            result.selectedElement
        );

        return result;
    }
}
