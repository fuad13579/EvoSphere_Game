#ifndef TURNMANAGER_H
#define TURNMANAGER_H

class TurnManager {
public:
    int currentPlayerIndex;
    int currentRound;

    TurnManager();
    int getCurrentPlayerIndex();
    int getCurrentRound();
    void nextTurn(int playerCount);
};

#endif