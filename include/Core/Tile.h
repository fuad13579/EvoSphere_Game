#ifndef TILE_H
#define TILE_H

#include "Utils/Constants.h"

using EvoSphere::TileType;

struct Tile
{
    int index = 0;
    TileType type = TileType::OriginGate;
    EvoSphere::ElementType elementType = EvoSphere::ElementType::None;
    const char* territoryName = "";
    const char* relatedName = "";
    bool ownable = false;
};

Tile createTile(int index, TileType type, const char* relatedName, int ownable);

int isTileOwnable(const Tile* tile);

#endif
