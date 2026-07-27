#include "Console/ConsoleGame.hpp"
#include "Systems/MovementSystem.h"

#include <string>

#include "Console/ConsoleInput.hpp"
#include "Console/ConsoleRenderer.hpp"
#include "Systems/BattleSystem.h"
#include "Systems/EventSystem.h"
#include "Core/Player.h"
#include "data/EvoranDatabase.hpp"

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
    const std::vector<EvoSphere::Evoran> starters = EvoSphere::createStarterEvorans();//Evorandatabase.cpp//

    for (int index = 0; index < playerCount; index++)
    {
        const std::string playerName = ConsoleInput::askPlayerName(index + 1);

        EvoSphere::initializePlayer(&players[index], index, playerName);//Player.h//
    }

    for (int index = 0; index < playerCount; index++)
    {
        const std::string& playerName = players[index].playerName;

        ConsoleRenderer::gameMessage(playerName + ", choose your avatar.");
        ConsoleRenderer::starterEvoranChoices(starters);
        const int starterChoice = ConsoleInput::askMenuChoice(1, static_cast<int>(starters.size()));

        EvoSphere::Evoran starter = starters[starterChoice - 1];
        EvoSphere::setOwnerId(&starter, index);
        EvoSphere::addEvoran(&players[index], starter);
        players[index].avatarName = EvoSphere::getEvoranName(&starter);

        ConsoleRenderer::gameMessage(playerName + " chose " + EvoSphere::getEvoranName(&starter) + "."
        );
    }
}

void ConsoleGame::movementSystem(EvoSphere::Player& currentPlayer, int playerIndex)
{
    int rollTotal = EvoSphere::rollEnergyOrbs();

    const int round = gameState.turnManager.getCurrentRound();
    if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Electric") &&
        currentPlayer.electricBonusRound != round)
    {
        rollTotal += 3;
        currentPlayer.electricBonusRound = round;
        ConsoleRenderer::gameMessage("Electric territory adds +3 movement this round.");
    }

    if (useOrbForgeMovementBonus(&gameState, playerIndex))
    {
        ++rollTotal;
        ConsoleRenderer::gameMessage("Orb Forge grants +1 movement this round.");
    }
    const int oldPosition = currentPlayer.currentPosition;

    EvoSphere::movePlayer(currentPlayer, rollTotal);

    const int newPosition = currentPlayer.currentPosition;

    ConsoleRenderer::gameMessage("Rolled: " + std::to_string(rollTotal));
    ConsoleRenderer::gameMessage("Old position: " + std::to_string(oldPosition));
    ConsoleRenderer::gameMessage("New position: " + std::to_string(newPosition));

    if (EvoSphere::didPassOriginGate(oldPosition, newPosition, rollTotal))
    {
        if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Water"))
        {
            EvoSphere::healAvatar(&currentPlayer, 5);
            ConsoleRenderer::gameMessage("Water territory restores 5 Avatar Points.");
        }
        const int specialTileGems = applySpecialTileOriginGateRewards(&gameState, currentPlayer.playerId);
        if (specialTileGems > 0)
        {
            ConsoleRenderer::gameMessage("Your owned special tiles gave you " + std::to_string(specialTileGems) + " extra Evolution Gem(s).");
        }
    }
}

void ConsoleGame::resolveLanding(int playerIndex)
{
    EvoSphere::Player& currentPlayer = players[playerIndex];
    Tile* tile = getTile(&gameState.board, currentPlayer.currentPosition);
    int selectedEvoranIndex = -1;
    EvoSphere::Evoran* attacker = nullptr;
    EvoSphere::Evoran* defender = nullptr;
    int attackerHpBefore = 0;
    int defenderHpBefore = 0;

    if (tile != nullptr &&
        (tile->tileType == EvoSphere::TileType::BlessingShrine ||
         tile->tileType == EvoSphere::TileType::ChaosRift))
    {
        const bool isBlessing = tile->tileType == EvoSphere::TileType::BlessingShrine;
        EvoSphere::EventResult event = isBlessing
            ? EvoSphere::generateBlessingShrineEvent()
            : EvoSphere::generateChaosRiftEvent();

        ConsoleRenderer::gameMessage(
            event.isMovementEvent
                ? (isBlessing ? "Blessing: move forward " : "Chaos: move backward ") +
                    std::to_string(event.movementAmount) + " tiles."
                : "Territory event selected."
        );

        const int round = gameState.turnManager.getCurrentRound();
        if (!isBlessing && event.isMovementEvent &&
            doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Air") &&
            currentPlayer.airProtectionRound != round)
        {
            currentPlayer.airProtectionRound = round;
            ConsoleRenderer::gameMessage("Air territory ignored this backward movement event.");
            return;
        }
        if (EvoSphere::ownsFullTerritory(currentPlayer, gameState.board, EvoSphere::ElementType::Mystic) &&
            currentPlayer.mysticRerollRound != round)
        {
            ConsoleRenderer::gameMessage("Use your Mystic reroll? 1. Yes  2. No");
            if (ConsoleInput::askMenuChoice(1, 2) == 1)
            {
                event = isBlessing
                    ? EvoSphere::generateBlessingShrineEvent()
                    : EvoSphere::generateChaosRiftEvent();
                currentPlayer.mysticRerollRound = round;
                ConsoleRenderer::gameMessage("Mystic reroll used.");
            }
        }

        EvoSphere::applyEventResult(currentPlayer, gameState.board, event);
        ConsoleRenderer::gameMessage(event.applied ? "Event applied." : "The territory event faded away.");
        return;
    }

    if (tile != nullptr && isOpponentOwnedEvoranTile(*tile, currentPlayer))
    {
        const int territoryBonus = EvoSphere::getTerritoryDefenseBonus(gameState.board, *tile, tile->ownerId);

        if (territoryBonus > 0)
        {
            ConsoleRenderer::gameMessage("The defender controls this territory and gains +" + std::to_string(territoryBonus) + " damage.");
        }

        defender = getDefendingEvoran(&gameState, *tile);

        if (defender == nullptr)
        {
            ConsoleRenderer::gameMessage("The tile defender could not be found.");
        }
        else if (!EvoSphere::canEvoranBattle(*defender))
        {
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(defender) + " is defeated and cannot defend this tile."
            );
        }
        else
        {
            std::vector<int> activeIndexes;
            for (int index = 0; index < static_cast<int>(currentPlayer.ownedEvorans.size()); ++index)
            {
                if (EvoSphere::canEvoranBattle(currentPlayer.ownedEvorans[index]))
                {
                    activeIndexes.push_back(index);
                }
            }

            if (activeIndexes.empty())
            {
                ConsoleRenderer::gameMessage("You have no active Evoran available to battle.");
            }
            else
            {
                ConsoleRenderer::activeEvoranChoices(currentPlayer);
                const int choice = ConsoleInput::askMenuChoice(1, static_cast<int>(activeIndexes.size()));
                selectedEvoranIndex = activeIndexes[choice - 1];

                attacker = &currentPlayer.ownedEvorans[selectedEvoranIndex];
                attackerHpBefore = EvoSphere::getCurrentHp(attacker);
                defenderHpBefore = EvoSphere::getCurrentHp(defender);
                ConsoleRenderer::gameMessage(
                    EvoSphere::getDisplayName(attacker) + " battles " +
                    EvoSphere::getDisplayName(defender) + "."
                );
            }
        }
    }

    const LandingResult result = resolvePlayerLanding(
        &gameState,
        playerIndex,
        selectedEvoranIndex
    );

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
        if (attacker != nullptr && defender != nullptr)
        {
            const int defenderDamageTaken = defenderHpBefore - EvoSphere::getCurrentHp(defender);
            const int attackerDamageTaken = attackerHpBefore - EvoSphere::getCurrentHp(attacker);

            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(attacker) + " attacked " +
                EvoSphere::getDisplayName(defender) + " for " +
                std::to_string(defenderDamageTaken) + " damage."
            );
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(defender) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(defender)) + "/" +
                std::to_string(EvoSphere::getMaxHp(defender))
            );

            if (attackerDamageTaken > 0)
            {
                ConsoleRenderer::gameMessage(
                    EvoSphere::getDisplayName(defender) + " counterattacked " +
                    EvoSphere::getDisplayName(attacker) + " for " +
                    std::to_string(attackerDamageTaken) + " damage."
                );
            }

            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(attacker) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(attacker)) + "/" +
                std::to_string(EvoSphere::getMaxHp(attacker))
            );

            if (EvoSphere::isDefeated(attacker))
            {
                ConsoleRenderer::gameMessage(EvoSphere::getDisplayName(attacker) + " has been defeated.");
            }

            if (EvoSphere::isDefeated(defender))
            {
                ConsoleRenderer::gameMessage(EvoSphere::getDisplayName(defender) + " has been defeated.");
            }

            if (EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Fire &&
                doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Fire"))
            {
                ConsoleRenderer::gameMessage("Fire territory increased the attacker's damage by 20%.");
            }

            if (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Fire &&
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Fire"))
            {
                ConsoleRenderer::gameMessage("Fire territory increased the defender's damage by 20%.");
            }

            if (EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Rock &&
                doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Rock"))
            {
                ConsoleRenderer::gameMessage("Rock territory reduced incoming damage to the attacker by 5.");
            }

            if (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Rock &&
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Rock"))
            {
                ConsoleRenderer::gameMessage("Rock territory reduced incoming damage to the defender by 5.");
            }

            if ((EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Dark &&
                 doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Dark")) ||
                (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Dark &&
                 doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Dark")))
            {
                ConsoleRenderer::gameMessage("Dark territory gives its Dark Evoran a 40% chance to dodge incoming damage.");
            }

            if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Nature") ||
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Nature"))
            {
                ConsoleRenderer::gameMessage("Nature territory healed its owner's Nature Evorans by 10 HP after battle.");
            }
        }

        ConsoleRenderer::gameMessage("Normal opponent-tile battle damage did not reduce Avatar Points.");
    }
    else if (result == LandingResult::SpecialTileAttuned && tile != nullptr)
    {
        const int progress = tile->attunementProgress[currentPlayer.playerId];
        ConsoleRenderer::gameMessage(
            "You attuned to " + getName(tile) + ". Progress: " +
            std::to_string(progress) + "/" +
            std::to_string(tile->requiredAttunement) + "."
        );
    }
    else if (result == LandingResult::SpecialTileClaimed && tile != nullptr)
    {
        ConsoleRenderer::gameMessage(
            "You reached " + std::to_string(tile->requiredAttunement) + "/" +
            std::to_string(tile->requiredAttunement) + " attunement and claimed " +
            getName(tile) + "."
        );
    }
    else if (result == LandingResult::OwnSpecialTile && tile != nullptr)
    {
        if (tile->index == EvoSphere::ANCIENT_RELIC_SHRINE_INDEX)
        {
            ConsoleRenderer::gameMessage("Ancient Relic Shrine grants +5 damage for your next wild Evoran battle.");
        }
        else
        {
            ConsoleRenderer::gameMessage("This special tile belongs to you.");
        }
    }
    else if (result == LandingResult::OpponentSpecialTile && tile != nullptr)
    {
        if (tile->index == EvoSphere::GEMSTONE_MINE_INDEX)
        {
            ConsoleRenderer::gameMessage("Gemstone Mine belongs to an opponent. Its owner gained 1 Evolution Gem.");
        }
        else if (tile->index == EvoSphere::ORB_FORGE_INDEX)
        {
            ConsoleRenderer::gameMessage("Orb Forge moved you backward 2 tiles.");
        }
        else
        {
            ConsoleRenderer::gameMessage("Ancient Relic Shrine removed 1 Evolution Gem if you had one.");
        }
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
                movementSystem(currentPlayer, currentPlayerIndex);
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
