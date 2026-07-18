#include "Core/Tile.h" // Uses the Tile struct and function declarations.

Tile createTile(int index, TileType type, const char* relatedId, int ownable) // Creates one Tile value.
{
    Tile tile; // Creates a local Tile variable.
    tile.index = index; // Saves the board position.
    tile.type = type; // Saves the tile category.
    tile.relatedName = relatedId;
    tile.ownable = ownable != 0;
    return tile; // Sends the completed Tile back to the caller.
}

int isTileOwnable(const Tile* tile) // Checks whether a tile can be owned.
{
    return tile != nullptr && tile->ownable; // Avoids null pointers and returns 1 or 0.
}
