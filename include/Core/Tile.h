#ifndef TILE_H // Prevents this file from being included more than once.
#define TILE_H // Marks this header as already included.

enum TileType { // Lists every type of board space.
    TILE_ORIGIN_GATE, // The starting tile that can give rewards when passed.
    TILE_WILD_EVORAN, // A tile with an Evoran that players can battle and capture.
    TILE_GUARDIAN, // A tile that applies a Guardian blessing or curse.
    TILE_TELEPORT_TERMINAL, // A tile that moves the player to another terminal.
    TILE_BLESSING_SHRINE, // A tile that gives a positive event or reward.
    TILE_CHAOS_RIFT, // A tile that gives a risky or negative event.
    TILE_SPECIAL_OWNABLE // A special tile that can be owned, such as a relic.
};

struct Tile { // Holds data for one board tile; it has no class methods.
    int index; // The tile position on the board, normally from 0 to 39.
    TileType type; // The kind of tile, selected from TileType above.
    const char* relatedId; // An Evoran or Guardian name; nullptr when not needed.
    int ownable; // 1 means a player can own this tile; 0 means they cannot.
};

Tile createTile(int index, TileType type, const char* relatedId, int ownable); // Creates and returns one tile.

int isTileOwnable(const Tile* tile); // Returns 1 if the tile can be owned, otherwise 0.

#endif // TILE_H
