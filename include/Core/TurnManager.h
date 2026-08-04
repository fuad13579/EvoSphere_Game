#ifndef TURNMANAGER_H
#define TURNMANAGER_H

struct TurnManager
{
    int currentPlayerIndex = 0;
    int currentRound = 1;
};

int getCurrentPlayerIndex(const TurnManager* turnManager);
int getCurrentRound(const TurnManager* turnManager);
void nextTurn(TurnManager* turnManager, int playerCount);

#endif
