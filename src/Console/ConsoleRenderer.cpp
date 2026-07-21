#include "Console/ConsoleRenderer.hpp"

#include <iostream>

void ConsoleRenderer::gameTitleIntroduction()
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "              E V O S P H E R E\n";
    std::cout << "========================================\n";
    std::cout << " Welcome to the World of Avatars and\n";
    std::cout << " Evorans!\n";
    std::cout << "========================================\n\n";
}

void ConsoleRenderer::gameRules()
{
    std::cout << "--------------- GAME RULES --------------\n";
    std::cout << "1. Players take turns.\n";
    std::cout << "2. Keep your avatar alive.\n";
    std::cout << "3. The last active player wins.\n";
    std::cout << "-----------------------------------------\n\n";
}

void ConsoleRenderer::playerStatus(const EvoSphere::Player& player)
{
    std::cout << "\n";
    std::cout << "------------- PLAYER STATUS -------------\n";
    std::cout << "Player Name:      " << player.playerName << "\n";
    std::cout << "Avatar Name:      " << player.avatarName << "\n";
    std::cout << "Avatar Points:    " << player.avatarPoints << "\n";
    std::cout << "Evolution Gems:   " << player.evolutionGems << "\n";
    std::cout << "Board Position:   " << player.currentPosition << "\n";
    std::cout << "Score:            " << player.score << "\n";
    std::cout << "-----------------------------------------\n\n";
}

void ConsoleRenderer::playerTurnStart(
    const EvoSphere::Player& player,
    int round)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "Round " << round << " | " << player.playerName << "'s Turn\n";
    std::cout << "========================================\n";
}

void ConsoleRenderer::starterEvoranChoices(const std::vector<EvoSphere::Evoran>& starters)
{
    std::cout << "\n----------- CHOOSE YOUR AVATAR -----------\n";

    for (std::size_t index = 0; index < starters.size(); index++)
    {
        std::cout << index + 1 << ". " << EvoSphere::getEvoranName(&starters[index]) << "\n";
    }

    std::cout << "-----------------------------------------\n";
}

void ConsoleRenderer::mainMenu(bool hasRolled)
{
    std::cout << "\n";
    std::cout << "--------------- MAIN MENU ---------------\n";
    std::cout << (hasRolled ? "1. End Turn\n" : "1. Roll the Orbs\n");
    std::cout << "2. View Stats\n";
    std::cout << "3. Quit Game\n";
    std::cout << "-----------------------------------------\n";
}

void ConsoleRenderer::gameWinner(const EvoSphere::Player& player)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "             GAME OVER\n";
    std::cout << "Winner: " << player.playerName << "\n";
    std::cout << "========================================\n";
}

void ConsoleRenderer::gameMessage(const std::string& message)
{
    std::cout << "\n> " << message << "\n";
}
