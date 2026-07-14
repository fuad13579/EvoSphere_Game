#include "Core/Player.h"

#include <algorithm>

namespace EvoSphere
{
    void initializePlayer(Player* player,int playerId,const std::string& avatarName)
    {
        if (player == nullptr)
        {
            return;
        }

        player->playerId = playerId;
        player->avatarName = avatarName;
        player->avatarPoints = STARTING_AVATAR_POINTS;
        player->evolutionGems = STARTING_EVOLUTION_GEMS;
        player->currentPosition = STARTING_POSITION;
        player->ownedEvorans.clear();//clear all evorans
        player->defeated = false;//reset defeated status
    }

    int getPlayerId(const Player* player)
    {
        return player == nullptr ? -1 : player->playerId;
    }

    const std::string& getAvatarName(const Player* player)
    {
        static const std::string emptyName;

        return player == nullptr ? emptyName : player->avatarName;
    }

    int getAvatarPoints(const Player* player)
    {
        return player == nullptr ? 0 : player->avatarPoints;
    }

    int getEvolutionGems(const Player* player)
    {
        return player == nullptr ? 0 : player->evolutionGems;
    }

    int getCurrentPosition(const Player* player)
    {
        return player == nullptr ? -1 : player->currentPosition;
    }

    void movePlayerTo(Player* player, int position)
    {
        if (player == nullptr)
        {
            return;
        }

        player->currentPosition = position % BOARD_SIZE;//

        if (player->currentPosition < 0)
        {
            player->currentPosition += BOARD_SIZE;
        }
    }

    void addEvolutionGems(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->evolutionGems += amount;
    }

    bool spendEvolutionGems(Player* player, int amount)
    {
        if (player == nullptr ||
            amount <= 0 ||
            player->evolutionGems < amount)
        {
            return false;
        }

        player->evolutionGems -= amount;
        return true;
    }

    void takeAvatarDamage(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->avatarPoints =
            std::max(0, player->avatarPoints - amount);

        player->defeated = player->avatarPoints <= 0;
    }

    void healAvatar(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->avatarPoints =
            std::min(MAX_AVATAR_POINTS,
                     player->avatarPoints + amount);

        player->defeated = player->avatarPoints <= 0;
    }

    void addEvoran(Player* player, const Evoran& evoran)
    {
        if (player == nullptr)
        {
            return;
        }

        player->ownedEvorans.push_back(evoran);
    }

    const std::vector<Evoran>& getOwnedEvorans(const Player* player)
    {
        static const std::vector<Evoran> emptyEvorans;

        return player == nullptr
            ? emptyEvorans
            : player->ownedEvorans;
    }

    bool hasOwnedEvorans(const Player* player)
    {
        return player != nullptr &&
               !player->ownedEvorans.empty();
    }

    Evoran* getStrongestEvoran(Player* player)
    {
        if (!hasOwnedEvorans(player))
        {
            return nullptr;
        }

        Evoran* strongest = &player->ownedEvorans[0];

        for (Evoran& evoran : player->ownedEvorans)
        {
            if (evoran.getDamage() > strongest->getDamage())
            {
                strongest = &evoran;
            }
        }

        return strongest;
    }

    bool isDefeated(const Player* player)
    {
        return player == nullptr ||
               player->avatarPoints <= 0;
    }

    bool isAlive(const Player* player)
    {
        return !isDefeated(player);
    }
}