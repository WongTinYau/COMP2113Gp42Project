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
};

#endif
