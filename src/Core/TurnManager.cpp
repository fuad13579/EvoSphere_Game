#include "Core/TurnManager.h"

int getCurrentPlayerIndex(const TurnManager* turnManager)
{
    return turnManager->currentPlayerIndex;
}

int getCurrentRound(const TurnManager* turnManager)
{
    return turnManager->currentRound;
}

void nextTurn(TurnManager* turnManager, int playerCount)
{
    ++turnManager->currentPlayerIndex;
    if (turnManager->currentPlayerIndex >= playerCount)
    {
        ++turnManager->currentRound;
        turnManager->currentPlayerIndex = 0;
    }
}
