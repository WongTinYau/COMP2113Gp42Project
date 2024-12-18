#include <iostream>
#include <fstream>
#include <string>
#include "help.h"
#include "RussianDudeLevel.h"
#include "CppDemonLevel.h"
#include "VanillaMode.h"
#include "Cutscene.h"
#include "GameState.h"
#include "newstats.h"
#include "SaveLoad.h"

using namespace std;

void main_menu();
void LevelSelectionMenu();
void HelpMenu();
void HardResetMenu();
void LoadGameMenu();
void ReturnToMainMenu();

void ReturnToMainMenu(){
    string command;
    cout << "Enter any key to return to main menu." << endl;
    cin >> command;
    main_menu();
}

void LevelSelectionMenu(){
    cout << string(30, '\n');
    cout << "Select a level to play" << endl;
    Statistics stats = GetStat();

    // set background color of cleared level to bright green

    cout << "\033[102m";    //set background color to bright green
    cout << "(Cleared level)";
    cout << "\033[40m" << endl;     // set background color back to black
    if (stats.RussianWon > 0){
        cout << "\033[102m";    //set background color to bright green
        cout << "Enter (1) for Russian Dude";
        cout << "\033[40m" << endl;;     // set background color back to black
    }
    else {
        cout << "Enter (1) for Russian Dude" << endl;
    }
    if (stats.DemonWon > 0){
        cout << "\033[102m";    //set background color to bright green
        cout << "Enter (2) for C++ Demon";
        cout << "\033[40m" << endl;;     // set background color back to black
    }
    else {
        cout << "Enter (2) for C++ Demon" << endl;
    }
    cout << "Enter (3) for Vanilla mode" << endl;
    cout << "Enter (r) to return to main menu" << endl;
    
    string Selection;
    bool validSelection = false;
    while (validSelection == false){
        cin >> Selection;
        if (Selection == "1" || Selection == "(1)"){
            
            // Prompt for New Game or Load Game
            cout << "Enter (n) for New Game or (c) to Continue Game: ";
            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                cutsceneO1();
                
                // Start a new game
                RussianDudeLevelWithSaveSupport(false);
            } else if (choice == 'c' || choice == 'C') {

                // Continue saved game
                RussianDudeLevelWithSaveSupport(true);
            } else {
                cout << "Invalid choice. Returning to main menu...\n";
                main_menu();
            }
        }
        else if (Selection == "2" || Selection == "(2)"){
            validSelection = true;
            
            // Prompt for New Game or Continue Game
            cout << "Enter (n) for New Game or (c) to Continue Game: ";
            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                cutsceneO2();
                
                // Start a new game
                CppDemonLevelWithSaveSupport(false);
            } else if (choice == 'c' || choice == 'C') {

                // Continue saved game
                CppDemonLevelWithSaveSupport(true);
            } else {
                cout << "Invalid choice. Returning to main menu...\n";
                main_menu();
            }
        }
        else if (Selection == "3" || Selection == "(3)"){
            validSelection = true;
            VanillaMode();
        }
        else if (Selection == "r" || Selection == "(r)" || Selection == "R"){
            validSelection = true;
            main_menu();
        }
        else{
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for Russian Dude" << endl;
            cout << "Enter (2) for C++ Demon" << endl;
            cout << "Enter (3) for Vanilla mode" << endl;
            cout << "Enter (r) to return to main menu" << endl;
        }
    }
}

void LoadGameMenu() {
    
    // Load the saved game state
    GameState state;
    if (LoadGame(state)) {
        cout << "Resuming saved game...\n";

        // Determine the level based on the saved state
        if (state.currentLevel == "RussianDude") {
            RussianDudeLevelWithSaveSupport(true);  // Resume Russian Dude Level
        } else if (state.currentLevel == "CppDemon") {
            CppDemonLevelWithSaveSupport(true);    // Resume C++ Demon Level
        } else {
            cout << "Error: Unknown level in saved game. Returning to main menu.\n";
            ReturnToMainMenu();
        }
    } else {
        cout << "No saved game found. Returning to main menu.\n";
        ReturnToMainMenu();
    }
}


void HelpMenu(){
    cout << string(30, '\n');
    cout << "Which part of the game would you like to learn about?" << endl;
    cout << "Enter (1) for Gameplay" << endl;
    cout << "Enter (2) for Supply phase" << endl;
    cout << "Enter (3) for Item phase" << endl;
    cout << "Enter (4) for Shooting phase" << endl;
    cout << "Enter (5) for Vanilla Mode" << endl;
    cout << "Enter (r) to return to main menu" << endl;
    string Selection;
    bool validSelection = false;
    while (validSelection == false){
        cin >> Selection;
        if (Selection == "1" || Selection == "(1)"){
            validSelection = true;
            GameplayHelp();
        }
        else if (Selection == "2" || Selection == "(2)"){
            validSelection = true;
            SupplyHelp();
        }
        else if (Selection == "3" || Selection == "(3)"){
            validSelection = true;
            ItemsHelp();
        }
        else if (Selection == "4" || Selection == "(4)"){
            validSelection = true;
            ShootHelp();
        }
        else if (Selection == "5" || Selection == "(5)"){
            validSelection = true;
            VanillaHelp();
        }
        else if (Selection == "r" || Selection == "(r)" || Selection == "R"){
            validSelection = true;
            main_menu();
        }
        else{
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for Gameplay" << endl;
            cout << "Enter (2) for Supply phase" << endl;
            cout << "Enter (3) for Item phase" << endl;
            cout << "Enter (4) for Shooting phase" << endl;
            cout << "Enter (5) for Vanilla Mode" << endl;
            cout << "Enter (r) to return to main menu" << endl;
        }
    }
}

void HardResetMenu(){
    // Warning message to prevent accidental reset
    cout << "\nAre you really sure to reset everything?" << endl;
    cout << "Enter 'YES' (without the ') to proceed." << endl;
    string command;
    cin >> command;
    if (command == "YES"){
        InitializeStat();
    }
    else{
        cout << "Decision aborted, returning to main menu." << endl;
    }
    ReturnToMainMenu();
}

void main_menu(){
    cout << string(30, '\n');
    cout << "Welcome to NEW RUSSIAN ROULETTE" << endl;
    cout << "Enter (1) for New Game" << endl;
    cout << "Enter (2) for Load Game" << endl;
    cout << "Enter (3) for Help" << endl;
    cout << "Enter (4) for Statistics" << endl;
    cout << "Enter (5) for HARD RESET" << endl;
    cout << "Enter (q) to Quit"<< endl;
    Statistics stats = GetStat();
    
    string userInput;
    bool validInput = false;
    while (validInput == false) {
        cin >> userInput;
        if (userInput == "1" || userInput == "(1)"){
            validInput = true;
            LevelSelectionMenu();
        }
        else if (userInput == "2" || userInput == "(2)"){
            validInput = true;
            LoadGameMenu();
        }
        else if (userInput == "3" || userInput == "(3)"){
            validInput = true;
            HelpMenu();
        }
        else if (userInput == "4" || userInput == "(4)"){
            validInput = true;
            PrintStat(stats);
        }
        else if (userInput == "5" || userInput == "(5)"){
            validInput = true;
            HardResetMenu();
        }
        else if (userInput == "q" || userInput == "(q)" || userInput == "Q"){
            SaveStat(stats);
            exit(0);
        }
        else {
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for New Game" << endl;
            cout << "Enter (2) for Load Game" << endl;
            cout << "Enter (3) for Help" << endl;
            cout << "Enter (4) for Statistics" << endl;
            cout << "Enter (5) for HARD RESET" << endl;
            cout << "Enter (q) to Quit"<< endl;
        }
    }
}

int main()
{
    // Check game data status
    ifstream file("data.txt");
    if (file.good()){
        cout << "Good file status!" << endl;
    } else{
        // Create a new data.txt if the file doesn't exist or the file is corrupted
        cout << "data.txt either doesn't exist or corrupted, now creating a new one." << endl;
        InitializeStat();
    }
    ReturnToMainMenu();
    return 0;
}
