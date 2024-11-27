#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <chrono>
#include "Shotgun.h"
#include "Entity.h"
#include "Item.h"
#include "Inventory.h"
#include "Shell.h"
#include "main.h"
#include "CppDemonLevel.h"
#include "ItemType.h"
#include "newstats.h"
using namespace std;

static void printStatus(Entity& player, Entity& dealer, Shotgun& shotgun) {
    cout << "------------------------------------------------------------\n";
    cout << "Player lives: " << player.getCurrentLives() << "/" << player.getMaxLives() << " | Dealer lives: " << dealer.getCurrentLives() << "/" << dealer.getMaxLives() << endl;
    cout << "Remaining shells: " << shotgun.getRemainingShells() << " | Remaining live shells: " << shotgun.getRemainingLiveShells() << endl;
}

int dealerChoose(Entity& dealer, int slotNumber, int chances) {

    if (slotNumber == -1) {
        if (chances <= (6 + dealer.getCurrentLives() * 3) ) { // 9 - 30%
            return 0;
        }
        return 1;
    }
    else if (slotNumber == -2) { // override from dealerUse()
        slotNumber = -1;
        return 0;
    }
    else if (slotNumber == -3) { // override from dealerUse()
        slotNumber = -1;
        return 1;
    }

    return 2;
}

int dealerUse(Entity& dealer, Entity& player, vector<Item>& dealerItemQueue, int& dealerNextChoice, int chances) {
    vector<Item> itemList = dealer.getInventory().getItems();

    if (dealerItemQueue.empty() and dealerNextChoice == -1) {
        for (int i = 0; i < itemList.size(); i++) {
            Item item = itemList[i];

            switch (item.getType()) {
            case ItemType::HEART:
                if (dealer.getCurrentLives() < dealer.getMaxLives()) {
                    return i;
                }
                break;

            case ItemType::MAGNET:
                if (!dealer.getInventory().isFull() && player.getInventory().getItemCount() > 0) {
                    return i;
                }
                break;

            case ItemType::HANDCUFF:
                return i;

            case ItemType::MAGNIFYING_GLASS:
                if (chances < 80 && chances > 20) {
                    return i;
                }
                break;

            case ItemType::SAW:
                if (chances > 70) {
                    dealerNextChoice = -3;
                    return i;
                }
                break;

            case ItemType::INVERTER:
                if (chances < 20) {
                    dealerNextChoice = -3;
                    return i;
                }
                break;

            default:
                cout << "The Dealer encountered an unknown item, gonna use it anyway.\n";
                return i;
            }
        }
        return dealerNextChoice;
    }
    else if (!dealerItemQueue.empty() and dealerNextChoice == -1) {
        while (!dealerItemQueue.empty()) {
            for (int i = 0; i < itemList.size(); i++) {
                Item item = itemList[i];
                if (item.getType() == dealerItemQueue.back().getType()) {
                    dealerItemQueue.pop_back();
                    return i;
                }
            }
            dealerItemQueue.pop_back();
        }
    }
    return dealerNextChoice;
}

bool playTurn(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer, vector<Item>& dealerItemQueue, int& dealerNextChoice) {
    if (isPlayerTurn) {
        if (!player.getInventory().getItemCount() == 0) {
            cout << "It is now your turn, you have the following items:\n";
            vector<Item> items = player.getInventory().getItems();
            for (int i = 0; i != items.size(); i++) {
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
        int choice = -1;
        int slotNumber = -1;
        int chances = (shotgun.getRemainingShells() > 0) ? (shotgun.getRemainingLiveShells() * 100) / shotgun.getRemainingShells() : 0;
        
        slotNumber = dealerUse(dealer, player, dealerItemQueue, dealerNextChoice, chances);
        dealerNextChoice = -1;
        choice = dealerChoose(dealer, slotNumber, chances);

        if (choice == 0) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on themselves...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                dealer.damage(result.second);
            }
            else {
                cout << "Click. It's a blank.\n";
                cout << "The Dealer gets to go again.\n";
                player.addPunishedRounds(1);
            }
        }

        else if (choice == 1) {
            pair<Shell, int> result = shotgun.shoot();
            cout << "The Dealer pulls the trigger on you...\n";
            if (result.first == Shell::LIVE) {
                cout << "BANG! You lose a life.\n";
                player.damage(result.second);
            }
            else {
                cout << "Click. It's a blank.\n";
            }
        }

        else if (choice == 2) {
            if (slotNumber != -1) {
                Item item = dealer.getInventory().getSlotItem(slotNumber);

                pair<bool, string> response = item.use(dealer, player, shotgun);
                cout << "Dealer uses item: " << toString(dealer.getInventory().getSlotItem(slotNumber).getType()) << endl;

                if (dealer.getInventory().getSlotItem(slotNumber).getType() == ItemType::MAGNIFYING_GLASS) {
                    if (response.second == "Magnifying Glass Used! The shell is Blank!") {
                        dealerNextChoice = -2;
                    }
                    else if (response.second == "Magnifying Glass Used! The shell is Live!") {
                        dealerNextChoice = -3;
                        dealerItemQueue.push_back(ItemType::SAW);
                    }
                    else cout << "Magnifying Glass Broken.";
                }

                dealer.getInventory().resetSlot(slotNumber);

                if (!response.first) {
                    cout << "The Dealer has some trouble using the item, retrying";
                }
            }
            return false;
        }

        if (player.getPunishedRounds() > 0) {
            player.reducePunishedRounds(1);
            return false;
        }
        else return true;
    }
}


void CppDemonLevel(){
    using namespace std::chrono;
    cout << "C++ Demon level entered successfully!\n";
    cout << "You and the Dealer will play to death.\n";

    auto startTime = high_resolution_clock::now();

    bool gameOnGoing = true;
    Shotgun* shotgun = nullptr;
    Entity* player = new Entity("Player", 6, 8);
    Entity* dealer = new Entity("Dealer", 8, 8);
    while (gameOnGoing) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist1(3, 7);
        int StartingLiveRound = dist1(gen);

        shotgun = new Shotgun(StartingLiveRound, 9, 1);
        player->getInventory().addRandomItems(4);
        dealer->getInventory().addRandomItems(4);

        bool isPlayerTurn = true;
        vector<Item> dealerItemQueue = {}; // for sequencial use of items
        int dealerNextChoice = -1; // for choice after item
        while (!shotgun->isEmpty() && player->getCurrentLives() > 0 && dealer->getCurrentLives() > 0) {
            printStatus(*player, *dealer, *shotgun);
            isPlayerTurn = playTurn(isPlayerTurn, *shotgun, *player, *dealer, dealerItemQueue, dealerNextChoice);
        }
        Statistics stats = GetStat();
        if (player->getCurrentLives() <= 0) {
            cout << "You lost all your lives. Game over.\n";
            stats.DemonLost++;
            gameOnGoing = false;
        }
        else if (dealer->getCurrentLives() <= 0) {
            cout << "The Dealer lost all their lives. You win!\n";
            stats.DemonWon++;
            gameOnGoing = false;
        }
        else {
            cout << "Both you and the Dealer have survived this round!\n";
            cout << "Let's see if you're this lucky the next round.\n";
            cout << "New round commencing.\n";
            dealerItemQueue = {};
            dealerNextChoice = -1; // clear after each round
        }
        SaveStat(stats);
    }
    delete shotgun;
    delete player;
    delete dealer;

    auto endTime = high_resolution_clock::now(); 
    auto duration = duration_cast<seconds>(endTime - startTime);
    long playTimeinSeconds = duration.count();
    AddTotalTime(playTimeinSeconds);

    string command;
    cout << "Enter any key to return to main menu.\n";
    cin >> command;
    main_menu();
}

