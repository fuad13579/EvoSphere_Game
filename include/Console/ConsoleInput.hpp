#pragma once

#include <string>

class ConsoleInput
{
public:
    static int askPlayerCount();
    static std::string askAvatarName(int playerNumber);
    static int askMenuChoice(int minimum, int maximum);
    static void waitForEnter();

private:
    static int readNumberInRange(
        const std::string& prompt,
        int minimum,
        int maximum
    );
};