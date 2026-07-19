#include "Console/ConsoleInput.hpp"

#include <iostream>
#include <limits> // For std::numeric_limits.

int ConsoleInput::askPlayerCount()
{
    int playerCount;

    while (1)
    {
        std::cout << "Number of players [2-3]: ";
        std::cin >> playerCount;

        if (std::cin.good() && playerCount >= 2 && playerCount <= 3)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return playerCount;
        }

        std::cout << "Invalid input.Need 2 to 3 Players\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

std::string ConsoleInput::askAvatarName(int playerNumber)
{
    std::string playerAvatar;

    std::cout << "Player " << playerNumber << "\n";
    std::cout << "Enter your avatar name: ";

    std::getline(std::cin, playerAvatar);

    return playerAvatar;
}

int ConsoleInput::askMenuChoice(int minimum, int maximum)
{
    int playerChoice;

    while (1)
    {
        std::cout << "Choose an option: ";

        std::cin >> playerChoice;

        if (std::cin.good() && playerChoice >= minimum && playerChoice <= maximum)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return playerChoice;
        }

        std::cout << "Invalid choice.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

void ConsoleInput::waitForEnter()
{
    std::string lastChoice;

    std::cout << "Press Enter to continue...";
    std::getline(std::cin, lastChoice);
}
