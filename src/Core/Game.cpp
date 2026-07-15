#include "Core/Game.h"

#include <iostream>

void initializeGameState(GameState* game, Player players[], int playerCount)
{
    if (game == nullptr)
    {
        return;
    }

    // The game points to the player array owned by the caller.
    game->players = players;//players=players means that the game struct's players pointer is set to point to the same memory location as the players array passed in as an argument. This allows the game struct to access and manipulate the player data directly.
    game->playerCount = playerCount < 0 ? 0 : playerCount;
    game->gameOver = false;
    game->winnerIndex = -1;
}

bool canPlayerTakeTurn(const Player* player)
{
    return player != nullptr && !isPlayerDefeated(player);
}

int countActivePlayers(const Player players[], int playerCount)
{
    if (players == nullptr || playerCount <= 0)
    {
        return 0;
    }

    int activeCount = 0;
    for (int i = 0; i < playerCount; ++i)
    {
        if (canPlayerTakeTurn(&players[i]))
        {
            ++activeCount;
        }
    }

    return activeCount;
}

int findWinnerIndex(const Player players[], int playerCount)
{
    if (players == nullptr || playerCount <= 0)
    {
        return -1;
    }

    int winnerIndex = -1;
    for (int i = 0; i < playerCount; ++i)
    {
        if (!canPlayerTakeTurn(&players[i]))
        {
            continue;
        }

        // If a second active player is found, there is no winner yet.
        if (winnerIndex != -1)
        {
            return -1;
        }

        winnerIndex = i;
    }

    return winnerIndex;
}

bool updateGameState(GameState* game)
{
    if (game == nullptr || game->players == nullptr || game->playerCount <= 0)
    {
        return false;
    }

    const int activeCount = countActivePlayers(game->players, game->playerCount);//const is used to indicate that the value of activeCount will not be modified after its initialization//                                                   
    if (activeCount <= 1)
    {
        // One active player left means the game is over.
        game->gameOver = true;
        game->winnerIndex = findWinnerIndex(game->players, game->playerCount);

        if (game->winnerIndex >= 0 && game->winnerIndex < game->playerCount)
        {
            std::cout << "Winner: " << game->players[game->winnerIndex].name << "\n";
        }

        return true;
    }

    game->gameOver = false;
    game->winnerIndex = -1;
    return true;//Indicates that game state was updated successfully and the game is still ongoing.
}
