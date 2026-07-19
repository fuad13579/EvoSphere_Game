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
        board->tiles[i] = boardTiles[i];//this line assigns the tile at index i in the board's tiles array to be equal to the corresponding tile in the boardTiles array. This effectively copies the data from the boardTiles array into the board's tiles array, initializing each tile on the game board with its starting values. The boardTiles array is defined in the Board.h header file and contains the starting values for each tile on the game board.

        if (board->tiles[i].type != EvoSphere::TileType::WildEvoran ||
            board->tiles[i].relatedName == nullptr ||
            board->tiles[i].relatedName[0] == '\0')
        {
            continue;
        }

        EvoSphere::findEvoranByName(
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
