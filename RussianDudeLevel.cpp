#include <iostream>
#include <string>
#include "main.h"
#include "RussianDudeLevel.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include "Shotgun.h"
#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "Shell.h"
#include "newstats.h"
#include "GameState.h"
#include "SaveLoad.h"

using namespace std;

static void printStatus(Entity& player, Entity& dealer, Shotgun& shotgun) {
    cout << "Player lives: " << player.getCurrentLives() << " | Dealer lives: " << dealer.getCurrentLives() << endl;
    cout << "Remaining shells: " << shotgun.getRemainingShells() << " | Remaining live shells: " << shotgun.getRemainingLiveShells() << endl;
}

bool playTurn(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer) {
    if (isPlayerTurn) {
        cout << "It is now your turn, you have the following items:" << endl;
        vector<Item> items = player.getInventory().getItems();
        for(int i = 0; i != items.size(); i++) {
            cout << "Slot " << i << ": " << toString(items[i].getType()) << endl;;
        }
        cout << "Choose your action: use item (u), shoot yourself (s) or shoot the Dealer (d): ";
        char choice;
        cin >> choice;

        if (choice == 's') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on yourself...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        } else if (choice == 'd') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on the Dealer...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        } else if (choice == 'u') {
            cout << "Choose your desired item's slot: ";
            int slotNumber;
            cin >> slotNumber;

            if (slotNumber >= 0 && slotNumber < player.getInventory().getItemCount()) {
                Item item = player.getInventory().getSlotItem(slotNumber);

                pair<bool, string> response = item.use(player, dealer, shotgun);
                cout << response.second << endl;

                if (response.first) {
                    player.getInventory().resetSlot(slotNumber);
                }
                return true;
            } else {
                cout << "Invalid slot number. You lose your turn." << endl;;
            }
        } else {
            cout << "Invalid choice. You lose your turn." << endl;
        }
        if (dealer.getPunishedRounds() > 0) {
           dealer.reducePunishedRounds(1);
           return true;
        } else return false;
    } else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 2);
        int choice = dist(gen);

        if (choice == 0) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on themselves...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }

        } else if (choice == 1) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on you...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        // @neonclathrate2(oscar) . @mingo128: You can make the AI smarter by not choosing to use an item when the AI has no items.
        } else if (choice == 2) {
            if (dealer.getInventory().getItemCount() > 0) { 
                uniform_int_distribution<int> itemDist(0, dealer.getInventory().getItemCount() - 1);
                int slotNumber = itemDist(gen);

                Item item = dealer.getInventory().getSlotItem(slotNumber);

                pair<bool, string> response = item.use(dealer, player, shotgun);
                cout << "Dealer uses item: " << response.second << endl;

                if (response.first) {
                    dealer.getInventory().resetSlot(slotNumber);
                }
                return false;
            } else {
                cout << "Dealer has no items to use. Skipping turn." << endl;
            }
        }
        if (player.getPunishedRounds() > 0) {
            player.reducePunishedRounds(1);
            return false;
        } else return true;
    }
}

bool playTurnVillian(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer) {
    if (isPlayerTurn) {
        cout << "It is now your turn, no item can be used in the Villian mode." << endl;

        cout << "Choose your action: shoot yourself (s) or shoot the Dealer (d): ";
        char choice;
        cin >> choice;

        if (choice == 's') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on yourself...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        } else if (choice == 'd') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on the Dealer...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        }
        if (dealer.getPunishedRounds() > 0) {
           dealer.reducePunishedRounds(1);
           return true;
        } else return false;
        } else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 2);
        int choice = dist(gen);

        if (choice == 0) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on themselves...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }

        } else if (choice == 1) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on you...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            } else {
                cout << "Click. It's a blank.\n";
            }
        } 
        if (player.getPunishedRounds() > 0) {
            player.reducePunishedRounds(1);
            return false;
        } else return true;
    }
}

void RussianDudeLevel(){
    cout << "Russian Dude level entered successfully!\n" << endl;
    
    Shotgun* shotgun = new Shotgun(2, 6, 1);
    Entity* player = new Entity("Player", 2, 4);
    Entity* dealer = new Entity("Dealer", 2, 4);
    player->getInventory().addRandomItems(4);
    dealer->getInventory().addRandomItems(4);

    bool isPlayerTurn = true;
    while (!shotgun->isEmpty() && player->getCurrentLives() > 0 && dealer->getCurrentLives() > 0) {
        printStatus(*player, *dealer, *shotgun);
        isPlayerTurn = playTurn(isPlayerTurn, *shotgun, *player, *dealer);
    }

    Statistics stats = GetStat();
    if (player->getCurrentLives() <= 0) {
        cout << "You lost all your lives. Game over.\n";
        stats.RussianLost++;
    } else if (dealer->getCurrentLives() <= 0) {
        cout << "The Dealer lost all their lives. You win!\n";
        stats.RussianWon++;
    } else {
        cout << "Both the Player and the Dealer have survived this round!\n";
        stats.RussianDraw++;
    }
    SaveStat(stats);

    delete shotgun;
    delete player;
    delete dealer;
    
    ReturnToMainMenu();
}

void ResumeRussianDudeLevel() {
    GameState state;

    // Load the saved game state
    if (LoadGame(state)) {
        // If a saved game is successfully loaded, print a message and resume the game
        cout << "Resuming saved game...\n";

        while (!state.shotgun.isEmpty() && state.player.getCurrentLives() > 0 && state.dealer.getCurrentLives() > 0) {
            printStatus(state.player, state.dealer, state.shotgun);

            state.isPlayerTurn = playTurn(state.isPlayerTurn, state.shotgun, state.player, state.dealer);

            // Save the game after every turn
            SaveGame(state);
        }

        Statistics stats = GetStat();
        if (state.player.getCurrentLives() <= 0) {
            cout << "You lost all your lives. Game over.\n";
            stats.RussianLost++;
        } else if (state.dealer.getCurrentLives() <= 0) {
            cout << "The Dealer lost all their lives. You win!\n";
            stats.RussianWon++;
        } else {
            cout << "Both the Player and the Dealer survived this round!\n";
            stats.RussianDraw++;
        }
        SaveStat(stats);

        ReturnToMainMenu();
    } else {
        // If no saved game exists, notify the user and start a new game
        cout << "No saved game found. Starting a new game instead...\n";
        RussianDudeLevel();
    }
}

// Start Game with Save/Load 
void RussianDudeLevelWithSaveSupport(bool continueGame = false) {
    if (continueGame) {
        // Load and resume the saved game
        ResumeRussianDudeLevel();
    } else {
        // Start a new game
        RussianDudeLevel();
    }
}
