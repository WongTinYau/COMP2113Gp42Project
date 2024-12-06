#include <iostream>
#include <string>
#include "main.h"
#include "VanillaMode.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include "Shotgun.h"
#include "Entity.h"
#include "Inventory.h"
#include "Shell.h"

using namespace std;

static void printStatus(Entity& player, Entity& dealer, Shotgun& shotgun) {
    cout << "------------------------------------------------------------\n";
    cout << "Player lives: " << player.getCurrentLives() << "/" << player.getMaxLives() << " | Dealer lives: " << dealer.getCurrentLives() << "/" << dealer.getMaxLives() << endl;
    cout << "Remaining shells: " << shotgun.getRemainingShells() << " | Remaining live shells: " << shotgun.getRemainingLiveShells() << endl;
}

bool playTurnVanilla(bool isPlayerTurn, Shotgun& shotgun, Entity& player, Entity& dealer) {
    if (isPlayerTurn) {
        cout << "It is now your turn, no item can be used in Vanilla mode." << endl;

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
                cout << "Lucky, you get to go again.\n";
                dealer.addPunishedRounds(1);
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
        } 
        if (player.getPunishedRounds() > 0) {
            player.reducePunishedRounds(1);
            return false;
        } else return true;
    }
}

void VanillaMode(){
    cout << "Vanilla mode entered successfully!\n" << endl;
    
    Shotgun* shotgun = new Shotgun(2, 6, 1);
    Entity* player = new Entity("Player", 2, 4);
    Entity* dealer = new Entity("Dealer", 2, 4);
    player->getInventory().addRandomItems(4);
    dealer->getInventory().addRandomItems(4);

    bool isPlayerTurn = true;
    while (!shotgun->isEmpty() && player->getCurrentLives() > 0 && dealer->getCurrentLives() > 0) {
        printStatus(*player, *dealer, *shotgun);
        isPlayerTurn = playTurnVanilla(isPlayerTurn, *shotgun, *player, *dealer);
    }

    if (player->getCurrentLives() <= 0) {
        cout << "You lost all your lives. Game over.\n";
    } else if (dealer->getCurrentLives() <= 0) {
        cout << "The Dealer lost all their lives. You win!\n";
    } else {
        cout << "Both the Player and the Dealer have survived this round!\n";
    }

    delete shotgun;
    delete player;
    delete dealer;
    
    ReturnToMainMenu();
}
