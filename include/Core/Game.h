#ifndef EVO_GAME_H
#define EVO_GAME_H

#include "Core/Board.h"
#include "Core/Player.h"
#include "Core/TurnManager.h"

enum class LandingResult
{
    Invalid,
    NoEffect,
    WildEvoranEncounter,
    OwnEvoranTile,
    OpponentEvoranTile
};

//Game information and state //
struct GameState
{
    Board board;
    EvoSphere::Player* players = nullptr;
    int playerCount = 0;
    bool gameOver = false;
    int winnerIndex = -1;
    TurnManager turnManager;
};

// Connects the players to a new game and resets its result state.
void initializeGameState(GameState* game, EvoSphere::Player players[], int playerCount);

// A player can continue while they are not defeated.
bool canPlayerTakeTurn(const EvoSphere::Player* player);

// Counts players who are still active.
int countActivePlayers(const EvoSphere::Player players[], int playerCount);

// Returns the winner index when exactly one player remains active.
int findWinnerIndex(const EvoSphere::Player players[], int playerCount);

// Recalculates the winner without changing the current turn.
bool refreshGameState(GameState* game);

// Recalculates the game-over state and records the winner.
bool updateGameState(GameState* game);

// Resolves the tile a player is standing on. A selected Evoran index starts a wild capture encounter.
LandingResult resolvePlayerLanding(GameState* game, int playerIndex, int selectedEvoranIndex = -1);

#endif
