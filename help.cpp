#include <iostream>
#include "help.h"
#include "main.h"

using namespace std;

void GameplayHelp(){
    cout << "Here is the rundown of the gameplay.\n" << endl;
    // Describe how the game is initialized upon entering a level
    cout << "Initialization" << endl;
    cout << "Both players should receive some random number of items at the start. (can be 0 if unlucky)" << endl;
    cout << "The rifle is loaded with 6 bullets, with number of functional bullets announced to both players." << endl;
    cout << "Of course the bullets are loaded in randomly." << endl;
    cout << "When the game starts, it is your turn.\n" << endl;
    // Describe actions available for each turn
    cout << "Turn actions" << endl;
    cout << "During a player's turn, a player may use any number of items available before shooting." << endl;
    cout << "Refer to the items section of the help menu for information about items" << endl;
    cout << "When a player decides to shoot, the player can choose 1 of the following." << endl;
    cout << "Shoot yourself\tShoot the opponent\n" << endl;
    // Shooting phase
    cout << "Shooting phase" << endl;
    cout << "The base damage of a functional bullet is 1, while it is 0 for non-functional." << endl;
    cout << "Since a bullet can be either functional or not, there are 4 cases to consider:" << endl;
    cout << "Case 1: Shoot yourself with a functional bullet" << endl;
    cout << "You lose life according to the current bullet damage, and pass the turn to your opponent." << endl;
    cout << "Case 2: Shoot yourself with a non-functional bullet" << endl;
    cout << "You lose no life, and you get an extra turn." << endl;
    cout << "Case 3: Shoot the opponent with a functional bullet" << endl;
    cout << "Opponent lose life according to the current bullet damage, and pass the turn to your opponent." << endl;
    cout << "Case 4: Shoot the opponent with a non-functional bullet" << endl;
    cout << "Opponent lose no life, and pass the turn to your opponent.\n" << endl;
    // Supply phase
    cout << "Supply phase" << endl;
    cout << "When there is no bullet left in the rifle, enter supply phase." << endl;
    cout << "The rifle is loaded randomly with a random number of bullets, ranging from 4 to 8." << endl;
    cout << "The number of functional bullets will be announced to both players." << endl;
    cout << "At the same time, both players should receive some random items in random quantity." << endl;
    cout << "The minimum number of total items received per player is 1." << endl;

    cout << "If a player has a full inventory, then that player will receive no item.\n" << endl;
    // End game
    cout << "How the game ends" << endl;
    cout << "The game ends when one of the players have the life total of 0 or below." << endl;
    cout << "That player loses the game, and the other player wins." << endl;
    cout << "As the game ends, you will be redirected to the main menu.\n" << endl;
    string Input;
    cout << "Enter any key to return to help menu" << endl;
    cin >> Input;
    help_menu();
}

void ItemsHelp(){
    cout << "Here is a list of items that will appear during gameplay." << endl;
    cout << "Saw: X2 damage of the upcoming shot, use at most once per turn" << endl;
    cout << "Magnifying glass: Check whether the current bullet is functional" << endl;
    cout << "Inverter: Invert the functionality of the current bullet.\n\tfunctional -> non-functional\n\tnon-functional -> functional" << endl;
    cout << "Heart: +1 life, cannot exceed life total" << endl;
    cout << "Handcuff: Apply to opponent, the applied player should skip 1 turn" << endl;
    cout << "Magnet: Steal 1 item from another player" << endl;
    cout << "\nPlease note that you have a limited inventory size, so use your items wisely!" << endl;
    string Input;
    cout << "Enter any key to return to help menu" << endl;
    cin >> Input;
    help_menu();
}
