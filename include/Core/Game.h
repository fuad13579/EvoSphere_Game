#ifndef EVO_GAME_H
#define EVO_GAME_H

#include "Core/Player.h"
#include "Core/TurnManager.h"

//Game information and state //
struct GameState
{
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

// Recalculates the game-over state and records the winner.
bool updateGameState(GameState* game);

#endif
