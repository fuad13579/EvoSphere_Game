#include "Console/ConsoleGame.hpp"
#include "Console/ConsoleInput.hpp"
#include "Console/ConsoleRenderer.hpp"


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
 
void ConsoleGame::createPlayers(int playerCount)
{
    initializeGameState(&gameState,players.data(),playerCount)
}

void ConsoleGame::setupGame()
{
    ConsoleRenderer::gameTitleIntroduction()
    ConsoleRenderer::gameRules()
    int playerCount = ConsoleInput::askPlayerCount();
    createPlayers(int playerCount);
    ConsoleRenderer::gameMessage();
    ConsoleInput::waitForEnter("Game setup is complete.");
}

void ConsoleGame::runTurn()
{
    int currentPlayerIndex = gameState.turnManager.getCurrentPlayerIndex();

    EvoSphere::Player& currentPlayer = players[currentPlayerIndex];

    ConsoleRenderer::playerTurnStart(currentPlayer,gameState.turnManager.getCurrentRound());

    ConsoleRenderer::mainMenu();

    int choice = ConsoleInput::askMenuChoice(1, 3);

    if (choice == 1)
    {
        ConsoleRenderer::Message("Turn ended.");
        updateGameState(&gameState);
    }
    else if (choice == 2)
    {
        ConsoleRenderer::playerStatus(currentPlayer);
        ConsoleInput::waitForEnter();
    }
    else if (choice == 3)
    {
        running = false;
        ConsoleRenderer::gameMessage("Game closed.");
    }
}