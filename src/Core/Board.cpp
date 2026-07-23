#include "Core/Board.h"

#include "data/BoardData.hpp"
#include "data/EvoranDatabase.hpp"

void initializeBoard(Board* board) // Fills a board with its starting tiles.
{
    if (board == nullptr)
    {
        return;
    }

    const auto boardTiles = EvoSphere::createBoardTiles();
    const auto wildEvorans = EvoSphere::createWildEvorans();

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        board->tiles[i] = boardTiles[i]; // Copies the fixed tile layout into the active board.

        if (board->tiles[i].type != EvoSphere::TileType::WildEvoran ||
            board->tiles[i].relatedName == nullptr ||
            board->tiles[i].relatedName[0] == '\0')
        {
            continue;
        }

        EvoSphere::findEvoranByName( // Loads the matching wild Evoran for this tile.
            wildEvorans,
            board->tiles[i].relatedName,
            &board->tiles[i].wildEvoran
        );
    }
}

Tile* getTile(Board* board, int index) // Finds one tile using its board index.
{
    if (board == nullptr || index < 0 || index >= BOARD_SIZE) return nullptr; // Rejects a missing board or invalid index.
    return &board->tiles[index]; // Returns the address of the requested tile.
}

const Tile* getTileConst(const Board* board, int index) // Finds one tile without allowing changes.
{
    if (board == nullptr || index < 0 || index >= BOARD_SIZE) return nullptr; // Rejects a missing board or invalid index.
    return &board->tiles[index]; // Returns read-only access to the requested tile.
}

bool setBoardTileOwner(Board* board, int index, int playerId) // Changes ownership through the board API.
{
    return setTileOwner(getTile(board, index), playerId); // Reuses Tile validation for the selected tile.
}

bool isBoardValid(const Board* board) // Checks that the board keeps the documented tile distribution.
{
    if (board == nullptr) return false; // A missing board cannot be valid.

    int originGates = 0; // Counts Origin Gate tiles.
    int wildEvorans = 0; // Counts wild Evoran tiles.
    int guardians = 0; // Counts Guardian tiles.
    int teleports = 0; // Counts Teleport Terminals.
    int blessings = 0; // Counts Blessing Shrines.
    int chaosRifts = 0; // Counts Chaos Rifts.
    int specialTiles = 0; // Counts special ownable tiles.

    for (int i = 0; i < BOARD_SIZE; ++i) // Checks every expected board position.
    {
        const Tile& tile = board->tiles[i]; // Reads the current tile.
        if (tile.index != i) return false; // Every tile must keep its matching index.

        switch (tile.type) // Adds this tile to the correct type count.
        {
        case EvoSphere::TileType::OriginGate: ++originGates; break;
        case EvoSphere::TileType::WildEvoran: ++wildEvorans; break;
        case EvoSphere::TileType::Guardian: ++guardians; break;
        case EvoSphere::TileType::Teleport: ++teleports; break;
        case EvoSphere::TileType::BlessingShrine: ++blessings; break;
        case EvoSphere::TileType::ChaosRift: ++chaosRifts; break;
        case EvoSphere::TileType::SpecialOwnable: ++specialTiles; break;
        }
    }

    return originGates == 1 && wildEvorans == EvoSphere::WILD_EVORAN_TILE_COUNT && // Confirms the complete 40-tile layout.
           guardians == EvoSphere::GUARDIAN_TILE_COUNT && teleports == EvoSphere::TELEPORT_TILE_COUNT &&
           blessings == EvoSphere::BLESSING_SHRINE_TILE_COUNT && chaosRifts == EvoSphere::CHAOS_RIFT_TILE_COUNT &&
           specialTiles == EvoSphere::SPECIAL_OWNABLE_TILE_COUNT;
}
