#ifndef CPPDEMONLEVEL_H
#define CPPDEMONLEVEL_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include "Shotgun.h"
#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "Shell.h"
#include "main.h"

using namespace std;

// Function to print the current status of the player, dealer, and the shotgun
void printStatus(Entity& player, Entity& dealer, Shotgun& shotgun);

// Function for the dealer to choose actions
int dealerChoose(Entity& dealer, int slotNumber, int chances);

// Function for the dealer to use items
int dealerUse(Entity& dealer, Entity& player, vector<Item>& dealerItemQueue, int& dealerNextChoice, int chances);

// Function to handle a turn of the game (either the player's or the dealer's)
bool playTurn(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer, vector<Item>& dealerItemQueue, int& dealerNextChoice);

// Main function to handle the C++ Demon Level game loop
void CppDemonLevel();

#endif // CPPDEMONLEVEL_H
