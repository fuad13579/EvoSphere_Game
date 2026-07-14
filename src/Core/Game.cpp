#include "Core/Game.h"

#include <iostream>

void initializeGameState(GameState* game, Player players[], int playerCount)
{
    if (game == nullptr)
    {
        return;
    }

    game->players = players;//players contains the name, health, score, and defeated status of each player in the game. It is initialized to nullptr, indicating that there are no players at the start of the game. The players array is set to the provided players parameter, which contains the actual player data.//
    game->playerCount = playerCount < 0 ? 0 : playerCount;
    game->gameOver = false;
    game->winnerIndex = -1;
}

bool canPlayerTakeTurn(const Player* player)
{
    return player != nullptr && !isPlayerDefeated(player); //True when the player is not null and has not been defeated, indicating that they can take their turn. Otherwise, it returns false.//
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
        if (canPlayerTakeTurn(&players[i])) //this function checks if a player can take their turn in the game. It takes a pointer to a Player structure as a parameter and returns true if the player is not null and has not been defeated, indicating that they can take their turn. Otherwise, it returns false.//
        {
            ++activeCount;//activecount is incremented by 1 for each player that can take their turn, indicating that they are still active in the game.//
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

    int winnerIndex = -1;//winnerIndex is initialized to -1, indicating that there is no winner at the start of the function. It will be updated if a player is found who can take their turn and is the only active player left in the game.//
    for (int i = 0; i < playerCount; ++i)
    {
        if (!canPlayerTakeTurn(&players[i]))
        {
            continue;
        }

        if (winnerIndex != -1)
        {
            return -1;
        }

        winnerIndex = i; //winnerIndex is i because it is the index of the winning player in the players array. If a player can take their turn, it checks if a winner has already been found (i.e., winnerIndex is not -1). If a winner has already been found, it returns -1, indicating that there is no clear winner. Otherwise, it sets the winnerIndex to the current player's index. After iterating through all players, it returns the winnerIndex, which will be -1 if there is no clear winner or the index of the winning player if there is one.//
    }

    return winnerIndex;
}

bool updateGameState(GameState* game)
{
    if (game == nullptr || game->players == nullptr || game->playerCount <= 0)
    {
        return false;
    }

    int activeCount = countActivePlayers(game->players, game->playerCount);
    if (activeCount <= 1)
    {
        game->gameOver = true;
        game->winnerIndex = findWinnerIndex(game->players, game->playerCount);
        if (game->winnerIndex >= 0 && game->winnerIndex < game->playerCount)
        {
            std::cout << "Winner: " << game->players[game->winnerIndex].name << "\n";
        }
        return true;
    }

    game->gameOver = false;//This line sets the game over status to false, indicating that the game is still ongoing. It is important to reset this status in case the game was previously marked as over but now has more than one active player.//
    game->winnerIndex = -1;
    return true;//The function then returns true, indicating that the game state was successfully updated and the game is still ongoing.//
}
