#pragma once

#include <string>

#include "Core/Player.h"

class ConsoleRenderer
{
public:
    static void gameTitleIntroduction();
    static void gameRules();

    static void playerStatus(const EvoSphere::Player& player);
    static void playerTurnStart( const EvoSphere::Player& player, int round);

    static void mainMenu(bool hasRolled);
    static void gameWinner(const EvoSphere::Player& player);

    static void gameMessage(const std::string& message);
};
