#include "Console/ConsoleGame.hpp"
#include "Systems/MovementSystem.h"

#include <string>

#include "Console/ConsoleInput.hpp"
#include "Console/ConsoleRenderer.hpp"
#include "Core/Player.h"

void ConsoleGame::run()
{
    setupGame();

    while (running && !gameState.gameOver)
    {
        runTurn();
    }

    if (gameState.gameOver && gameState.winnerIndex >= 0 && gameState.winnerIndex < gameState.playerCount)
    {
        ConsoleRenderer::gameWinner(players[gameState.winnerIndex]);
    }
}

void ConsoleGame::setupGame()
{
    ConsoleRenderer::gameTitleIntroduction();
    ConsoleRenderer::gameRules();

    const int playerCount = ConsoleInput::askPlayerCount();
    createPlayers(playerCount);

    initializeGameState(
        &gameState,
        players.data(),
        playerCount
    );

    ConsoleRenderer::gameMessage("Game setup is complete.");
    ConsoleInput::waitForEnter();
}

void ConsoleGame::createPlayers(int playerCount)
{
    players.resize(playerCount);

    for (int index = 0; index < playerCount; ++index)
    {
        const std::string avatarName = ConsoleInput::askAvatarName(index + 1);

        EvoSphere::initializePlayer(&players[index], index, avatarName);
    }
}

void ConsoleGame::movementSystem(EvoSphere::Player& currentPlayer)
{
    const int rollTotal = EvoSphere::rollEnergyOrbs();
    const int oldPosition = currentPlayer.currentPosition;

    EvoSphere::movePlayer(currentPlayer, rollTotal);

    const int newPosition = currentPlayer.currentPosition;

    ConsoleRenderer::gameMessage("Rolled: " + std::to_string(rollTotal));
    ConsoleRenderer::gameMessage("Old position: " + std::to_string(oldPosition));
    ConsoleRenderer::gameMessage("New position: " + std::to_string(newPosition));
}

void ConsoleGame::resolveLanding(int playerIndex)
{
    const LandingResult result = resolvePlayerLanding(&gameState, playerIndex);

    if (result == LandingResult::WildEvoranEncounter)
    {
        ConsoleRenderer::gameMessage("You found a wild Evoran. A capture encounter can begin when you have an active Evoran.");
    }
    else if (result == LandingResult::OwnEvoranTile)
    {
        ConsoleRenderer::gameMessage("This Evoran tile belongs to you. You are safe.");
    }
    else if (result == LandingResult::OpponentEvoranTile)
    {
        ConsoleRenderer::gameMessage("Opponent Evoran damage was applied to your Avatar Points.");
    }
}

void ConsoleGame::runTurn()
{
    const int currentPlayerIndex = gameState.turnManager.getCurrentPlayerIndex();
    EvoSphere::Player& currentPlayer = players[currentPlayerIndex];
    bool turnEnded = false;
    bool hasRolled = false;

    ConsoleRenderer::playerTurnStart(currentPlayer,gameState.turnManager.getCurrentRound());

    while (running && !turnEnded)
    {
        ConsoleRenderer::mainMenu(hasRolled);

        const int choice = ConsoleInput::askMenuChoice(1, 3);

        if (choice == 1)
        {
            if (!hasRolled)
            {
                movementSystem(currentPlayer);
                resolveLanding(currentPlayerIndex);
                hasRolled = true;

                if (gameState.gameOver)
                {
                    turnEnded = true;
                }
            }
            else
            {
                turnEnded = true;
                ConsoleRenderer::gameMessage("Turn ended.");
                updateGameState(&gameState);
            }
        }
        else if (choice == 2)
        {
            ConsoleRenderer::playerStatus(currentPlayer);
            ConsoleInput::waitForEnter();
        }
        else
        {
            running = false;
            ConsoleRenderer::gameMessage("Game closed.");
        }
    }
}
