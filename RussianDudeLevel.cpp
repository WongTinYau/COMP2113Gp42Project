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
#include <chrono>

using namespace std;

static void printStatus(Entity& player, Entity& dealer, Shotgun& shotgun) {
    cout << "------------------------------------------------------------\n";
    cout << "Player lives: " << player.getCurrentLives() << "/" << player.getMaxLives() << " | Dealer lives: " << dealer.getCurrentLives() << "/" << dealer.getMaxLives() << endl;
    cout << "Remaining shells: " << shotgun.getRemainingShells() << " | Remaining live shells: " << shotgun.getRemainingLiveShells() << endl;
}

bool playTurn(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer) {
    if (isPlayerTurn) {
        if (!player.getInventory().getItemCount() == 0) {
            cout << "It is now your turn, you have the following items:\n";
            vector<Item> items = player.getInventory().getItems();
            for (size_t i = 0; i != items.size(); i++) {
                cout << "Slot " << i << ": " << toString(items[i].getType()) << endl;
            }
            cout << "You can have at most " << player.getInventory().getMaxInventorySlots() << " items.\n";
        }
        else cout << "You have no items.\n";
        cout << "The Dealer have " << dealer.getInventory().getItemCount() << "/" << dealer.getInventory().getMaxInventorySlots() << " items.\n";

        cout << "Choose your action: use item (u), shoot yourself (s), shoot the Dealer (d) or quit game(q): ";
        char choice;
        cin >> choice;

        if (choice == 's') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on yourself...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            }
            else {
                cout << "Click. It's a blank.\n";
                cout << "Lucky, you get to go again.\n";
                dealer.addPunishedRounds(1);
            }
        }
        else if (choice == 'd') {
            pair<Shell, int> result = shotgun.shoot();
            cout << "You pull the trigger on the Dealer...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            }
            else {
                cout << "Click. It's a blank.\n";
            }
        }
        else if (choice == 'u') {
            if (player.getInventory().getItemCount() == 0) {
                cout << "You have no items to use. You lose your turn.\n";
                return false;
            }

            int slotNumber;
            while (true) {
                cout << "Choose your desired item's slot (0 to " << player.getInventory().getItemCount() - 1 << "): ";
                cin >> slotNumber;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid slot number.\n";
                    continue; // re-prompt player
                }

                if (slotNumber >= 0 && slotNumber < player.getInventory().getItemCount()) {
                    Item item = player.getInventory().getSlotItem(slotNumber);

                    pair<bool, string> response = item.use(player, dealer, shotgun);
                    cout << response.second << endl;

                    if (response.first) {
                        player.getInventory().resetSlot(slotNumber);
                    }
                    return true;
                }

                cout << "Invalid slot number. Please enter a number between 0 and "
                    << player.getInventory().getItemCount() - 1 << ".\n";
            }

        }
        else if (choice == 'q') {
            cout << "Quiting...\n";
            main_menu();
        }
        else {
            cout << "Invalid choice. You lose your turn." << endl;
        }
        if (dealer.getPunishedRounds() > 0) {
            dealer.reducePunishedRounds(1);
            return true;
        }
        else return false;
    }

    else { // start of AI logic
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
                cout << "The Dealer gets to go again.\n";
                player.addPunishedRounds(1);
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

void RussianDudeLevel(){
    using namespace std::chrono;
    cout << "Russian Dude level entered successfully!\n" << endl;

    auto startTime = high_resolution_clock::now();
    
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
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(endTime - startTime);
    long playTimeinSeconds = duration.count();
    stats.TotalTime += playTimeinSeconds;
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
void RussianDudeLevelWithSaveSupport(bool continueGame) {
    if (continueGame) {
        // Load and resume the saved game
        ResumeRussianDudeLevel();
    } else {
        // Start a new game
        RussianDudeLevel();
    }
}
