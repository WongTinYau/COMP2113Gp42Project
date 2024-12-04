#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include "Entity.h"
#include "Item.h"
#include "Shotgun.h"

struct GameState {
    std::string currentLevel;
    Entity player;
    Entity dealer;
    Shotgun shotgun;
    bool isPlayerTurn;
    std::vector<Item> dealerItemQueue;
    int dealerNextChoice;
    long totalPlayTime;

    GameState(const std::string& level = "RussianDudeLevel", 
              const Entity& playerEntity = Entity("Player", 2, 4),
              const Entity& dealerEntity = Entity("Dealer", 2, 4),
              const Shotgun& gun = Shotgun(2, 6, 1),
              bool playerTurn = true,
              const std::vector<Item>& itemQueue = {},
              int nextChoice = -1,
              long playTime = 0)
        : currentLevel(level), 
          player(playerEntity), 
          dealer(dealerEntity), 
          shotgun(gun), 
          isPlayerTurn(playerTurn), 
          dealerItemQueue(itemQueue), 
          dealerNextChoice(nextChoice), 
          totalPlayTime(playTime) {}
};

#endif
