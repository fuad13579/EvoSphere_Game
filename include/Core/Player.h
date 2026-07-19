#pragma once

#include <string>
#include <vector>

#include "Core/Evoran.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    struct Player
    {
        int playerId = 0;
        std::string avatarName;
        int avatarPoints = STARTING_AVATAR_POINTS;
        int evolutionGems = STARTING_EVOLUTION_GEMS;
        int currentPosition = STARTING_POSITION;
        std::vector<Evoran> ownedEvorans;
        bool defeated = false;
        bool noActiveEvoranPenaltyApplied = false;
        int score = 0;//Changed by Musfiq to merge Game.cpp and Player.cpp//
    };

    void initializePlayer(Player* player,int playerId,const std::string& avatarName);

    int getPlayerId(const Player* player);
    const std::string& getAvatarName(const Player* player);
    int getAvatarPoints(const Player* player);
    int getEvolutionGems(const Player* player);
    int getCurrentPosition(const Player* player);

    void movePlayerTo(Player* player, int position);

    void addEvolutionGems(Player* player, int amount);
    bool spendEvolutionGems(Player* player, int amount);

    void takeAvatarDamage(Player* player, int amount);
    void healAvatar(Player* player, int amount);

    void addEvoran(Player* player, const Evoran& evoran);

    const std::vector<Evoran>& getOwnedEvorans(const Player* player);
    bool hasOwnedEvorans(const Player* player);
    bool hasActiveEvorans(const Player* player);
    void updateNoActiveEvoranPenalty(Player* player);
    Evoran* getStrongestEvoran(Player* player);

    bool isDefeated(const Player* player);
    bool isAlive(const Player* player);
}
