#pragma once

#include <vector>

#include "Core/Game.h"

class ConsoleGame
{
public:
    void run();

private:
    GameState gameState;
    std::vector<EvoSphere::Player> players;
    bool running = true;

    void setupGame();
    void createPlayers(int playerCount);// Collects player names, then lets every player choose one starter avatar.//
    void movementSystem(EvoSphere::Player& currentPlayer, int playerIndex);
    void resolveLanding(int playerIndex);
    void runTurn();
};
