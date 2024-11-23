#include <iostream>
#include <string>
#include <ctime>
#include "help.h"
#include "RussianDudeLevel.h"
#include "CppDemonLevel.h"
#include "Cutscene.h"
#include "stats.h"

using namespace std;

// Functions used here
void main_menu();
void level_selection_menu();
void help_menu();


void level_selection_menu(){
    cout << "Select a level to play" << endl;
    cout << "Enter (1) for Russian Dude" << endl;
    cout << "Enter (2) for C++ Demon" << endl;
    cout << "Enter (r) to return to main menu" << endl;
    string Selection;
    bool validSelection = false;
    while (validSelection == false){
        cin >> Selection;
        if (Selection == "1" || Selection == "(1)"){
            validSelection = true;
            cutsceneO1();
            RussianDudeLevel();
        }
        else if (Selection == "2" || Selection == "(2)"){
            validSelection = true;
            cutsceneO1();
            CppDemonLevel();
        }
        else if (Selection == "r" || Selection == "(r)" || Selection == "R"){
            validSelection = true;
            main_menu();
        }
        else{
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for Russian Dude" << endl;
            cout << "Enter (2) for C++ Demon" << endl;
            cout << "Enter (r) to return to main menu" << endl;
        }
    }
}

void help_menu(){
    cout << "Which part of the game would you like to learn about?" << endl;
    cout << "Enter (1) for Gameplay" << endl;
    cout << "Enter (2) for Items" << endl;
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
            ItemsHelp();
        }
        else if (Selection == "r" || Selection == "(r)" || Selection == "R"){
            validSelection = true;
            main_menu();
        }
        else{
            cout << "Invalid User Input. Please try again." << endl;
            cout << "Enter (1) for Gameplay" << endl;
            cout << "Enter (2) for Items" << endl;
            cout << "Enter (r) to return to main menu" << endl;
        }
    }
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
    Statistics stat(0,0,0,0,0,0);
    time_t startTime = time(nullptr);
    string userInput;
    bool validInput = false;
    while (validInput == false) {
        cin >> userInput;
        if (userInput == "1" || userInput == "(1)"){
            validInput = true;
            level_selection_menu();
        }
        else if (userInput == "2" || userInput == "(2)"){
            cout << "This feature is broken now, sorry!" << endl;
            // Load/Continue game mechanics to be implemented
        }
        else if (userInput == "3" || userInput == "(3)"){
            validInput = true;
            help_menu();
        }
        else if (userInput == "4" || userInput == "(4)"){
            validInput = true;
            stats();
        }
        else if (userInput == "5" || userInput == "(5)"){
            validInput = true;
            hardReset();
        }
        else if (userInput == "q" || userInput == "(q)" || userInput == "Q"){
            TimeStat(stat,startTime);
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
    main_menu();
    return 0;
}
