#include <iostream>
#include "help.h"
#include "main.h"

using namespace std;

// Functions used
void GameplayHelp();
void ShootHelp();
void SupplyHelp();
void ItemsHelp();
void ReturnHelpMenu();
//
void GameplayHelp(){
    cout << "\nHere is the rundown of the gameplay.\n" << endl;
    // Describe how the game is initialized upon entering a level
    cout << "Initialization" << endl;
    cout << "Both players should receive 4 random items." << endl;
    cout << "The shotgun is fully loaded, live shells and blank shells are loaded in randomly." << endl;
    cout << "Capacity of shotgun" << endl;
    cout << "Russian Dude level: 6" << endl;
    cout << "C++ Demon level: 9" << endl;
    cout << "The number of live shells is announced to both players." << endl;
    cout << "After initialization, it is your turn.\n" << endl;
    // Describe actions available for each turn
    cout << "Each turn consists of 3 phases (in order):" << endl;
    cout << "Supply phase -> Item phase -> Shooting phase" << endl;
    cout << "Please refer to the corresponding section of the help menu for details regarding each phase." << endl;
    cout << "When entering commands, please refer strictly to the character indicated, and exclude ()." << endl;
    cout << "Else you will lose a turn as punishment.\n" << endl;
    // End game
    cout << "End game" << endl;
    cout << "For Russian Dude level, there are 2 cases." << endl;
    cout << "Case 1: No one dies (i.e. life total <= 0) when there is no shots left, the game ends in a draw." << endl;
    cout << "Case 2: One of the player died, then the surviving player wins and the dead player loses."<< endl;
    cout << "For C++ Demon level, the game continues until one of the players reached the life total of 0 or below." << endl;
    cout << "(i.e. game won't end when there is no shots left, because restock happens)" << endl;
    cout << "That player loses the game, and the other player wins." << endl;
    ReturnHelpMenu();
}

void ShootHelp(){
    cout << "\nWhen a player decides to shoot, the player can choose 1 of the following." << endl;
    cout << "Shoot yourself\tShoot the opponent\n" << endl;
    cout << "Here are 4 possible scenarios in shooting phase." << endl;
    cout << "Case 1: Shoot yourself with a live shell" << endl;
    cout << "You lose life according to the current shell damage, and pass the turn to your opponent." << endl;
    cout << "Case 2: Shoot yourself with a blank shell" << endl;
    cout << "You lose no life, and you get an extra turn." << endl;
    cout << "Case 3: Shoot the opponent with a live shell" << endl;
    cout << "Opponent lose life according to the current shell damage, and pass the turn to your opponent." << endl;
    cout << "Case 4: Shoot the opponent with a blank shell" << endl;
    cout << "Opponent lose no life, and pass the turn to your opponent.\n" << endl;
    cout << "How is shell damage calculated?" << endl;
    cout << "Base damage: live shell = 1, blank shell = 0" << endl;
    cout << "If saw is applied: shell damage = 2 x base damage.\n" << endl;
    ReturnHelpMenu();
}

void SupplyHelp(){
    cout << "\nSupply phase." << endl;
    cout << "Russian Dude level doesn't have this phase." << endl;
    cout << "This phase is automatically skipped when there is shell left in shotgun." << endl;
    cout << "i.e. Supply phase happens only if there is no shell left in the shotgun." << endl;
    cout << "The rifle is loaded randomly with live shells and blank shells." << endl;
    cout << "The number of live shells will be announced to both players." << endl;
    cout << "At the same time, both players should receive some random items in random quantity." << endl;
    cout << "The total number of items for both player is 4 when supply phase ends.\n" << endl;
    cout << "FAQ: Do I keep unused items from last turn?" << endl;
    cout << "Ans: Yes.\n" << endl;
    ReturnHelpMenu();
}

void ItemsHelp(){
    cout << "\nItem phase is a phase when a player decide to use items.\n" << endl;
    cout << "A player can use as many items as available (except Saw)." << endl;
    cout << "List of items that will appear during gameplay." << endl;
    cout << "Saw: X2 damage of the upcoming shot, use at most once per turn" << endl;
    cout << "Magnifying glass: Check whether the current shell is live or blank" << endl;
    cout << "Inverter: Invert the current shell status\n\ti.e. live -> blank  or  blank -> live" << endl;
    cout << "Heart: +1 life, cannot exceed life total" << endl;
    cout << "Handcuff: Apply to opponent, the applied player should skip 1 turn" << endl;
    cout << "Magnet: Steal a random item from another player\n" << endl;
    cout << "Inventory size" << endl;
    cout << "Russian Dude level: 4 (both players)" << endl;
    cout << "C++ Demon level: 8 (both players)" << endl;
    cout << "Players cannot stack items beyond inventory size, so use items wisely!" << endl;
    ReturnHelpMenu();
}

void ReturnHelpMenu(){
    string Input;
    cout << "\nEnter any key to return to help menu: ";
    cin >> Input;
    HelpMenu();
}
