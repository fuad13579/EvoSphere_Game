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
    std::cout << "Name:             " << player.avatarName << "\n";
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
    std::cout << "Round " << round << " | " << player.avatarName << "'s Turn\n";
    std::cout << "========================================\n";
}

void ConsoleRenderer::mainMenu()
{
    std::cout << "\n";
    std::cout << "--------------- MAIN MENU ---------------\n";
    std::cout << "1. End Turn\n";
    std::cout << "2. View Stats\n";
    std::cout << "3. Quit Game\n";
    std::cout << "-----------------------------------------\n";
}

void ConsoleRenderer::gameWinner(const EvoSphere::Player& player)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "             GAME OVER\n";
    std::cout << "Winner: " << player.avatarName << "\n";
    std::cout << "========================================\n";
}

void ConsoleRenderer::gameMessage(const std::string& message)
{
    std::cout << "\n> " << message << "\n";
}