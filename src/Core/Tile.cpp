#include "Core/Tile.h" // Uses the Tile struct and function declarations.

Tile createTile(int index, TileType type, const char* relatedId, int ownable) // Creates one Tile value.
{
    Tile tile; // Creates a local Tile with the safe defaults from Tile.h.
    tile.index = index; // Saves the board position.
    tile.type = type; // Saves the tile category.
    tile.relatedName = relatedId == nullptr ? "" : relatedId; // Avoids storing a null name.
    tile.ownable = ownable != 0; // Converts any non-zero value to true.
    return tile; // Sends the completed Tile back to the caller.
}

bool isTileOwnable(const Tile* tile) // Checks whether a tile can be owned.
{
    return tile != nullptr && tile->ownable; // Avoids null pointers.
}

bool isTileOwned(const Tile* tile) // Checks whether an ownable tile has an owner.
{
    return isTileOwnable(tile) && tile->ownerId >= 0; // Player IDs start at zero.
}

bool isTileOwnedBy(const Tile* tile, int playerId) // Checks the owner without changing tile data.
{
    return playerId >= 0 && isTileOwned(tile) && tile->ownerId == playerId; // Rejects invalid player IDs.
}

bool setTileOwner(Tile* tile, int playerId) // Changes ownership or clears it with -1.
{
    if (tile == nullptr || !tile->ownable || playerId < -1) return false; // Rejects missing tiles and invalid IDs.
    tile->ownerId = playerId; // Stores the player ID or -1 for no owner.
    return true; // Reports that the change succeeded.
}

const EvoSphere::Evoran* getWildEvoran(const Tile* tile) // Reads the Evoran stored on a wild tile.
{
    if (tile == nullptr || tile->type != TileType::WildEvoran) return nullptr; // Only wild tiles have a battle Evoran.
    return &tile->wildEvoran; // Returns read-only access to the tile's Evoran.
}

bool setWildEvoran(Tile* tile, const EvoSphere::Evoran* evoran) // Copies battle data onto a wild tile.
{
    if (tile == nullptr || evoran == nullptr || tile->type != TileType::WildEvoran) return false; // Validates both inputs.
    tile->wildEvoran = *evoran; // Copies the Evoran so the board owns its own data.
    return true; // Reports that the copy succeeded.
}
