#include <cassert> // Uses assert to stop the test when a condition is false.

#include "Core/Board.h" // Uses the Board functions being tested.

int main() // Runs the Board logic checks.
{
    Board board; // Creates one board for the test.
    initializeBoard(&board); // Loads the documented 40-tile layout.

    assert(isBoardValid(&board)); // Confirms every tile index and type count is correct.
    assert(getTile(&board, 0)->type == EvoSphere::TileType::OriginGate); // Confirms tile zero is Origin Gate.
    assert(getTile(&board, 1)->type == EvoSphere::TileType::WildEvoran); // Confirms the first normal tile is wild.
    assert(getTile(&board, -1) == nullptr); // Rejects a negative index safely.
    assert(getTileConst(&board, BOARD_SIZE) == nullptr); // Rejects an index after tile 39 safely.

    assert(setBoardTileOwner(&board, 1, 0)); // Lets player zero own a wild Evoran tile.
    assert(isTileOwnedBy(getTileConst(&board, 1), 0)); // Confirms that ownership was stored.
    assert(!setBoardTileOwner(&board, 0, 0)); // Prevents players from owning Origin Gate.

    return 0; // Reports success when every assertion passes.
}
