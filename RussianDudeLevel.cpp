#include<iostream>
#include<string>
#include"main.h"
#include"RussianDudeLevel.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

enum Shell { BLANK, LIVE };

void loadShotgun(vector<Shell>& shotgun) {
    shotgun.clear();
    int liveCount = 2;
    for (int i = 0; i < 6; ++i) {
        if (liveCount > 0) {
            shotgun.push_back(LIVE);
            --liveCount;
        } else {
            shotgun.push_back(BLANK);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(shotgun.begin(), shotgun.end(), g);
}

void printStatus(int playerLives, int dealerLives, int remainingShells, int remainingLiveShells) {
    cout << "Player lives: " << playerLives << " | Dealer lives: " << dealerLives 
         << " | Remaining shells: " << remainingShells << " | Remaining live shells: " << remainingLiveShells << endl;
}

bool playTurn(bool isPlayerTurn, vector<Shell>& shotgun, int& playerLives, int& dealerLives, int& remainingLiveShells) {
    Shell currentShell = shotgun.back();
    shotgun.pop_back();

    if (currentShell == LIVE) {
        --remainingLiveShells;
    }

    if (isPlayerTurn) {
        char choice;
        cout << "Choose your action: shoot yourself (s) or shoot the Dealer (d): ";
        cin >> choice;

        if (choice == 's') {
            cout << "You pull the trigger on yourself...\n";
            if (currentShell == LIVE) {
                cout << "BANG! You lose a life.\n";
                --playerLives;
                return false;
            } else {
                cout << "Click. It's a blank.\n";
            }
        } else if (choice == 'd') {
            cout << "You pull the trigger on the Dealer...\n";
            if (currentShell == LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                --dealerLives;
            } else {
                cout << "Click. It's a blank.\n";
            }
            return false;
        } else {
            cout << "Invalid choice. You lose your turn.\n";
        }
    } else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, 1);
        char choice = dist(gen) == 0 ? 's' : 'p';

        if (choice == 's') {
            cout << "The Dealer pulls the trigger on themselves...\n";
            if (currentShell == LIVE) {
                cout << "BANG! The Dealer loses a life.\n";
                --dealerLives;
                return true;
            } else {
                cout << "Click. It's a blank.\n";
            }
        } else if (choice == 'p') {
            cout << "The Dealer pulls the trigger on you...\n";
            if (currentShell == LIVE) {
                cout << "BANG! You lose a life.\n";
                --playerLives;
            } else {
                cout << "Click. It's a blank.\n";
            }
            return true;
        }
    }
    return isPlayerTurn;
}

void RussianDudeLevel(){
    cout << "Russian Dude level entered successfully!" << endl;
    
    int playerLives = 2;
    int dealerLives = 2;
    vector<Shell> shotgun;

    loadShotgun(shotgun);

    int remainingLiveShells = count(shotgun.begin(), shotgun.end(), LIVE);

    bool isPlayerTurn = true;
    while (!shotgun.empty() && playerLives > 0 && dealerLives > 0) {
        printStatus(playerLives, dealerLives, shotgun.size(), remainingLiveShells);
        isPlayerTurn = playTurn(isPlayerTurn, shotgun, playerLives, dealerLives, remainingLiveShells);
    }

    if (playerLives <= 0) {
        cout << "You lost all your lives. Game over.\n";
    } else if (dealerLives <= 0) {
        cout << "The Dealer lost all their lives. You win!\n";
    } else {
        cout << "Both the Player and the Dealer have survived this round!\n";
    }
    
    string command;
    cout << "Enter any key to return to main menu." << endl;
    cin >> command;
    main_menu();
}
