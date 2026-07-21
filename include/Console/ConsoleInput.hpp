#pragma once

#include <string>

class ConsoleInput
{
public:
    static int askPlayerCount();//Ask players number//
    static std::string askPlayerName(int playerNumber);//Ask each player's name//
    static int askMenuChoice(int minimum, int maximum);//Ask each player to chose a option from menu//
    static void waitForEnter();//Ask to press Enter to start the game??
};
