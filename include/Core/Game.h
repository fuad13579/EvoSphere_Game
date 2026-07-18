#ifndef EVO_GAME_H
#define EVO_GAME_H

#include <string>

#include "Core/TurnManager.h"

// Represents a player in the game.//
struct Player
{
    std::string name;
    bool defeated = false;
    int health = 100;
    int score = 0;
    int boardPosition = 0;
    int evolutionGems = 0;
};

//Game information and state //
struct GameState
{
    Player* players = nullptr;
    int playerCount = 0;
    bool gameOver = false;
    int winnerIndex = -1;
    TurnManager turnManager;
};

// Connects the players to a new game and resets its result state.
void initializeGameState(GameState* game, Player players[], int playerCount);

// A player can continue while they are not defeated.
bool canPlayerTakeTurn(const Player* player);

// Counts players who are still active.
int countActivePlayers(const Player players[], int playerCount);

// Returns the winner index when exactly one player remains active.
int findWinnerIndex(const Player players[], int playerCount);

// Recalculates the game-over state and records the winner.
bool updateGameState(GameState* game);

// Health reaching zero also means the player is defeated.
inline bool isPlayerDefeated(const Player* player)
{
    return player != nullptr && (player->defeated || player->health <= 0);
}

#endif
