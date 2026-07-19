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
    void createPlayers(int playerCount);
    void movementSystem(EvoSphere::Player& currentPlayer);
    void runTurn();
};