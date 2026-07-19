#pragma once

#include <array>

#include "Core/Board.h"
#include "Core/Player.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    bool isTeleportTile(const Tile& tile);// This function checks if the given tile is a teleport tile.

    int chooseDestination(
        int currentTeleportIndex,const std::array<int, TELEPORT_TILE_COUNT>& teleportIndexes
    );// This function allows the player to choose a destination teleport tile from the available teleport tiles. It takes the current teleport index and an array of teleport indexes as parameters. The function returns the index of the chosen destination teleport tile.

    bool teleportPlayer(Player& player, Board& board);//#pragma once

#include <array>

#include "Core/Board.h"
#include "Core/Player.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    bool isTeleportTile(const Tile& tile);

    int chooseDestination(
        int currentTeleportIndex,
        const std::array<int, TELEPORT_TILE_COUNT>& teleportIndexes
    );// Chooses a random Teleport Terminal destination.
// The current terminal is excluded, so the player moves to one of the other three terminals.

    bool teleportPlayer(Player& player, Board& board);// This function handles the teleportation of a player on the game board. It takes references to the player and the game board as parameters. The function first checks if the player is on a teleport tile. If so, it retrieves the indexes of all available teleport tiles on the board and allows the player to choose a destination teleport tile using the chooseDestination function. If a valid destination is chosen, the player's current position is updated to the chosen teleport tile index, and the function returns true, indicating that the teleportation was successful. If the player is not on a teleport tile or no valid destination is chosen, the function returns false, indicating that teleportation did not occur.
}
}