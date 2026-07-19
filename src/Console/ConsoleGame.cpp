#include "Console/ConsoleGame.hpp"

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

    if (gameState.gameOver &&
        gameState.winnerIndex >= 0 &&
        gameState.winnerIndex < gameState.playerCount)
    {
        ConsoleRenderer::gameWinner(players[gameState.winnerIndex]);
    }
}

void ConsoleGame::createPlayers(int playerCount)
{
    players.resize(playerCount);

    for (int index = 0; index < playerCount; ++index)
    {
        const std::string avatarName =
            ConsoleInput::askAvatarName(index + 1);

        EvoSphere::initializePlayer(
            &players[index],
            index,
            avatarName
        );
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

void ConsoleGame::runTurn()
{
    const int currentPlayerIndex =
        gameState.turnManager.getCurrentPlayerIndex();
    EvoSphere::Player& currentPlayer = players[currentPlayerIndex];

    ConsoleRenderer::playerTurnStart(
        currentPlayer,
        gameState.turnManager.getCurrentRound()
    );
    ConsoleRenderer::mainMenu();

    const int choice = ConsoleInput::askMenuChoice(1, 3);

    if (choice == 1)
    {
        ConsoleRenderer::gameMessage("Turn ended.");
        updateGameState(&gameState);
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
