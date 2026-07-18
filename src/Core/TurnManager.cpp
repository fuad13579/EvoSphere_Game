#include "Core/TurnManager.h"

TurnManager::TurnManager()
{
    currentPlayerIndex = 0;
    currentRound = 1;
}

int TurnManager::getCurrentPlayerIndex()
{
    return currentPlayerIndex;
}

int TurnManager::getCurrentRound()
{
    return currentRound;
}

void TurnManager::nextTurn(int playerCount)
{
    currentPlayerIndex++;
    if (currentPlayerIndex >= playerCount)
    {
        currentRound++;
        currentPlayerIndex = 0;
    }
}