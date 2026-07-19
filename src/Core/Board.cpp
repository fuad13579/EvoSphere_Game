#include "Core/Board.h"

#include "data/BoardData.hpp"
#include "data/EvoranDatabase.hpp"

namespace EvoSphere{

void initializeBoard(Board* board) // Fills a board with its starting tiles.
{
    if (board == nullptr)
    {
        return;
    }

    const auto boardTiles = createBoardTiles();//this function creates an array of tiles that represent the game board, with a size defined by the constant BOARD_SIZE. Each tile is an instance of the Tile struct, which holds data for one board tile, including its index, type, related ID, and ownable status. The function returns the array of tiles, which can be used to initialize the game board.
    const auto wildEvorans = createWildEvorans();//this function creates a vector of wild Evoran creatures that can be found on the game board. Each Evoran is an instance of the Evoran struct, which holds data for one creature, including its name, evolved name, element type, category, maximum HP, current HP, damage, evolved maximum HP, evolved damage, evolution status, and owner ID. The function returns the vector of wild Evorans, which can be used to populate the game board with these creatures.

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        board->tiles[i] = boardTiles[i];//this line assigns the tile at index i in the board's tiles array to be equal to the corresponding tile in the boardTiles array. This effectively copies the data from the boardTiles array into the board's tiles array, initializing each tile on the game board with its starting values. The boardTiles array is defined in the Board.h header file and contains the starting values for each tile on the game board.

        if (board->tiles[i].type != TileType::WildEvoran ||
            board->tiles[i].relatedName == nullptr ||
            board->tiles[i].relatedName[0] == '\0')
        {
            continue;
        }

        findEvoranByName(
            wildEvorans,
            board->tiles[i].relatedName,
            &board->tiles[i].wildEvoran
        );//this function searches for a wild Evoran in the wildEvorans vector by its name, which is stored in the relatedName field of the current tile. If a matching Evoran is found, its data is copied into the wildEvoran field of the current tile. This allows each tile on the game board to be associated with a specific wild Evoran creature, which can be encountered and interacted with during gameplay.
    }
}

Tile* getTile(Board* board, int index) // Finds one tile using its board index.
{
    if (board == nullptr || index < 0 || index >= BOARD_SIZE) return nullptr; // Rejects a missing board or invalid index.
    return &board->tiles[index]; // Returns the address of the requested tile.
}

}