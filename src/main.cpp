#include "Engine/Application.h"
#include "Console/ConsoleGame.hpp"

#include <string>

int main(int argumentCount, char* arguments[])
{
    if (argumentCount > 1 && std::string(arguments[1]) == "--terminal")
    {
        ConsoleGameState consoleGame;
        runConsoleGame(&consoleGame);
        return 0;
    }

    return EvoSphereGui::runApplication();
}
