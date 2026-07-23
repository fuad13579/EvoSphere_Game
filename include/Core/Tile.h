#ifndef TILE_H
#define TILE_H

#include "Core/Evoran.h"
#include "Utils/Constants.h"

using EvoSphere::TileType;

struct Tile // Stores data for one board space; it has no class methods.
{
    int index = 0; // The position of this tile from 0 to 39.
    TileType type = TileType::OriginGate; // The kind of board space.
    EvoSphere::ElementType elementType = EvoSphere::ElementType::None; // Its elemental type when relevant.
    const char* territoryName = ""; // The territory this tile belongs to.
    const char* relatedName = ""; // The Evoran, Guardian, or relic name on the tile.
    bool ownable = false; // True only when a player can own this tile.
    EvoSphere::Evoran wildEvoran; // The wild Evoran placed here, when this is a wild tile.
    int ownerId = -1; // -1 means that no player owns this tile.
};

Tile createTile(int index, TileType type, const char* relatedName, int ownable); // Creates a basic tile safely.

bool isTileOwnable(const Tile* tile); // Returns true when a tile can be owned.
bool isTileOwned(const Tile* tile); // Returns true when an ownable tile has an owner.
bool isTileOwnedBy(const Tile* tile, int playerId); // Checks whether one player owns the tile.
bool setTileOwner(Tile* tile, int playerId); // Sets a valid owner, or -1 to clear ownership.
const EvoSphere::Evoran* getWildEvoran(const Tile* tile); // Returns the wild Evoran only for wild tiles.
bool setWildEvoran(Tile* tile, const EvoSphere::Evoran* evoran); // Copies an Evoran onto a wild tile.

#endif
