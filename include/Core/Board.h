#ifndef BOARD_H // Prevents this file from being included more than once.
#define BOARD_H // Marks this header as already included.

#include "Core/Tile.h" // Uses the Tile struct for every board space.

const int BOARD_SIZE = EvoSphere::BOARD_SIZE; // Uses the shared 40-tile board size.

struct Board { // Holds all tiles that make up one game board.
    Tile tiles[BOARD_SIZE]; // Stores the 40 tiles from index 0 to 39.
};

void initializeBoard(Board* board); // Creates the starting layout of the board.
Tile* getTile(Board* board, int index); // Returns a tile pointer, or nullptr for an invalid index.
const Tile* getTileConst(const Board* board, int index); // Reads a tile without allowing changes.
bool setBoardTileOwner(Board* board, int index, int playerId); // Changes ownership for one tile.
bool isBoardValid(const Board* board); // Confirms all 40 tile indexes and type counts are correct.

#endif // BOARD_H
