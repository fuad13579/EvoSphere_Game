#include <cassert> // Uses assert to stop the test when a condition is false.

#include "Core/Board.h" // Uses the Board functions being tested.

int main() // Runs the Board logic checks.
{
    Tile origin = createTile(0, EvoSphere::TileType::OriginGate, EvoSphere::ElementType::None, "", "", false); // Creates an Origin Gate tile.
    Tile wild = createTile(1, EvoSphere::TileType::WildEvoran, EvoSphere::ElementType::Nature, "Nature", "Mossari", true); // Creates a Wild Evoran tile.
    Tile guardian = createTile(10, EvoSphere::TileType::Guardian, EvoSphere::ElementType::Mystic, "Guardian", "Solvyrion", false); // Creates a Guardian tile.
    Tile teleport = createTile(5, EvoSphere::TileType::Teleport, EvoSphere::ElementType::None, "", "", false); // Creates a Teleport tile.
    assert(getIndex(&origin) == 0 && getName(&origin) == "Origin Gate"); // Checks Origin Gate creation and getters.
    assert(getTileType(&wild) == EvoSphere::TileType::WildEvoran && getElementType(&wild) == EvoSphere::ElementType::Nature); // Checks Wild Evoran data.
    assert(getLinkedEvoranName(&guardian) == "Solvyrion" && getTileType(&teleport) == EvoSphere::TileType::Teleport); // Checks Guardian and Teleport creation.
    assert(setOwnerId(&wild, 1) && isOwned(&wild) && isOwnedBy(&wild, 1) && isOwnedByOpponent(&wild, 0)); // Checks Tile ownership functions.
    assert(setLinkedEvoranName(&wild, "Florayn") && getLinkedEvoranName(&wild) == "Florayn" && getTerritoryName(&wild) == "Nature"); // Checks linked-name and territory functions.

    Board board; // Creates one board for the test.
    initializeBoard(&board); // Loads the documented 40-tile layout.

    assert(isBoardValid(&board)); // Confirms every tile index and type count is correct.
    assert(getBoardSize(&board) == EvoSphere::BOARD_SIZE); // Confirms that the Board stores exactly 40 tiles.
    assert(getTile(&board, 0)->tileType == EvoSphere::TileType::OriginGate); // Confirms tile zero is Origin Gate.
    assert(getTile(&board, 1)->tileType == EvoSphere::TileType::WildEvoran); // Confirms the first normal tile is wild.
    assert(getTile(&board, -1) == nullptr); // Rejects a negative index safely.
    assert(getTileConst(&board, EvoSphere::BOARD_SIZE) == nullptr); // Rejects an index after tile 39 safely.
    assert(getTeleportTileIndexes(&board).size() == EvoSphere::TELEPORT_TILE_COUNT); // Confirms all four Teleport Terminal positions are stored.
    assert(getEvoranOnTile(&board, 1) != nullptr && getEvoranOnTile(&board, 1)->name == "Mossari"); // Confirms Wild Evoran data is connected to its tile.

    assert(setTileOwner(&board, 1, 0)); // Lets player zero own a wild Evoran tile.
    assert(isOwnedBy(getTileConst(&board, 1), 0)); // Confirms that ownership was stored.
    assert(!setTileOwner(&board, 0, 0)); // Prevents players from owning Origin Gate.
    assert(setTileOwner(&board, 3, 0) && setTileOwner(&board, 4, 0)); // Gives player zero every Nature territory tile.
    assert(doesPlayerOwnTerritory(&board, 0, "Nature")); // Confirms complete Nature territory ownership.
    assert(getTerritoryTiles(&board, "Nature").size() == 3); // Confirms all Nature territory tile indexes are returned.

    EvoSphere::Evoran updatedEvoran = *getEvoranOnTile(&board, 1); // Copies the Wild Evoran before updating it.
    updatedEvoran.currentHp = 1; // Changes its battle state for the update test.
    assert(updateEvoranOnTile(&board, 1, updatedEvoran)); // Updates the Wild Evoran through the Board API.
    assert(getEvoranOnTile(&board, 1)->currentHp == 1); // Confirms the updated battle state was stored.

    return 0; // Reports success when every assertion passes.
}
