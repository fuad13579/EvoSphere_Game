#ifndef TILE_H
#define TILE_H

#include "Core/Evoran.h"
#include "Utils/Constants.h"

using EvoSphere::TileType;

// Default values give every new tile a safe starting state.
// The real tile information is set in BoardData.cpp.

struct Tile
{
    int index = 0;
    TileType type = TileType::OriginGate;
    EvoSphere::ElementType elementType = EvoSphere::ElementType::None;
    const char* territoryName = "";
    const char* relatedName = "";
    bool ownable = false;

    EvoSphere::Evoran wildEvoran;
    int ownerId = -1;
};

Tile createTile(int index, TileType type, const char* relatedName, int ownable);

int isTileOwnable(const Tile* tile);

#endif
