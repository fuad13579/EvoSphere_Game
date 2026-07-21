#pragma once

#include <string>
#include <vector>

#include "Core/Evoran.h"
#include "Core/Player.h"

class ConsoleRenderer
{
public:
    static void gameTitleIntroduction();//Display game name//
    static void gameRules();//Disolay game rules//

    static void playerStatus(const EvoSphere::Player& player);//Display player stats//
    static void playerTurnStart( const EvoSphere::Player& player, int round);//Display round & player number//
    static void starterEvoranChoices(const std::vector<EvoSphere::Evoran>& starters);//Fucntion for choosing preselcted Player Avater

    static void mainMenu(bool hasRolled);//Display main menu depending on value of hasRolled//
    static void gameWinner(const EvoSphere::Player& player);//Display winner//

    static void gameMessage(const std::string& message);
};
