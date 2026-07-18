#include "Core/Board.h" // Uses the Board struct and its function declarations.

void initializeBoard(Board* board) // Fills a board with its starting tiles.
{
    if (board == nullptr) return; // Stops safely when no board was given.

    for (int i = 0; i < BOARD_SIZE; ++i) // Goes through all 40 board positions.
    {
        board->tiles[i] = createTile(i, EvoSphere::TileType::WildEvoran, nullptr, 1); // Starts each normal tile as ownable.
    }

    board->tiles[0] = createTile(0, EvoSphere::TileType::OriginGate, nullptr, 0); // Makes the first tile the non-ownable Origin Gate.
}

Tile* getTile(Board* board, int index) // Finds one tile using its board index.
{
    if (board == nullptr || index < 0 || index >= BOARD_SIZE) return nullptr; // Rejects a missing board or invalid index.
    return &board->tiles[index]; // Returns the address of the requested tile.
}
