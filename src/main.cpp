#include "Engine/Application.h"
#include "Console/ConsoleGame.hpp"

#include <string>

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string(argv[1]) == "--terminal")
    {
        ConsoleGameState consoleGame;
        runConsoleGame(&consoleGame);
        return 0;
    }// If the "--terminal" argument is provided, run the console version of the game.

    return EvoSphereGui::runApplication();// Otherwise, run the GUI version of the game.
}
