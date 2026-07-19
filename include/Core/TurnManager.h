#ifndef TURNMANAGER_H
#define TURNMANAGER_H

class TurnManager {
public:
    int currentPlayerIndex;
    int currentRound;

    TurnManager();
    int getCurrentPlayerIndex();//Used in ConsoleGame.cpp//
    int getCurrentRound();//Used in ConsoleGame.cpp//
    void nextTurn(int playerCount);
};

#endif