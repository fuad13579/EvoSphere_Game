#include "Core/Game.h"

#include <iostream>//this line includes the iostream library, which provides functionalities for input and output operations in C++. It allows us to use std::cout for printing messages to the console and std::cin for reading user input from the console.//
#include <string>

int main()
{
    Player players[2];
    players[0].name = "Player 1";
    players[1].name = "Player 2";

    GameState game;
    initializeGameState(&game, players, 2);

    std::cout << "EvoSphere Terminal Demo\n";
    std::cout << "Starting game...\n";

    while (!game.gameOver)
    {
        std::cout << "\nCurrent players:\n";
        for (int i = 0; i < game.playerCount; ++i)
        {
            std::cout << i + 1 << ". " << game.players[i].name;
            if (isPlayerDefeated(&game.players[i]))
            {
                std::cout << " [defeated]";
            }
            std::cout << "\n";
        }

        std::cout << "Enter 'q' to quit or any other key to continue: ";
        std::string input;
        std::cin >> input;

        if (input == "q" || input == "Q")
        {
            break;
        }

        for (int i = 0; i < game.playerCount; ++i)
        {
            if (!isPlayerDefeated(&game.players[i]))
            {
                game.players[i].defeated = true;
                break;
            }
        }

        updateGameState(&game);
    }

    std::cout << "\nGame finished.\n";
    return 0;
}
