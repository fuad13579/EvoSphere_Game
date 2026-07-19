#pragma once

#include <string>

#include "Core/Player.h"

class ConsoleRenderer
{
public:
    static void gameTitleIntroduction();//Display game name//
    static void gameRules();//Disolay game rules//

    static void playerStatus(const EvoSphere::Player& player);//Display player stats//
    static void playerTurnStart( const EvoSphere::Player& player, int round);//Display round & player number//

    static void mainMenu(bool hasRolled);//Display main menu depending on value of hasRolled//
    static void gameWinner(const EvoSphere::Player& player);//Display winner//

    static void gameMessage(const std::string& message);
};
