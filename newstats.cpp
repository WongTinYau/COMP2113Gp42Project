#include <iostream>
#include <fstream>
#include <string>
#include "main.h"
using namespace std;

struct Statistics{
    // statistics stored in file
    int RussianWon;
    int RussianLost;
    int RussianDraw;
    int DemonWon;
    int DemonLost;
    int TotalTime; //in seconds

    // derived statistics
    int TotalGames;
    int RussianGames;
    int DemonGames;

    // Constructor
    Statistics(int a, int b, int c, int d, int e, int f){
        RussianWon = a;
        RussianLost = b;
        RussianDraw = c;
        DemonWon = d;
        DemonLost = e;
        TotalTime = f;

        TotalGames = a + b + c + d + e;
        RussianGames = a + b + c;
        DemonGames = d + e;
    }
};

void InitializeStat(){
    // Create a file "data.txt" to store game statistics
    // Replaces the old "data.txt" if available
    // Format: 6 integers on the same line, separated by ' '
    // Content: stats.RussianWon stats.RussianLost stats.RussianDraw stats.DemonWon stats.DemonLost stats.TotalTime
    ofstream fout;
    fout.open("data.txt");
    if ( fout.fail() ) {
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    fout << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0;
    fout.close();
}

Statistics GetStat(){
    // Get statistics from data.txt
    // Return a struct object with type Statistics
    ifstream fin;
    fin.open("data.txt");
    if ( fin.fail() ) {
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    int a, b, c, d, e, f;
    fin >> a >> b >> c >> d >> e >> f;
    fin.close();
    return Statistics(a, b, c, d, e, f);
}

void SaveStat(Statistics stats){
    // Save statistics to data.txt
    ofstream fout;
    fout.open("data.txt");
    if ( fout.fail() ) {
        cout << "Error in file opening!" << endl;
        exit(1);
    }
    fout << stats.RussianWon << ' ' << stats.RussianLost << ' ' << stats.RussianDraw << ' '<< stats.DemonWon << ' ' << stats.DemonLost << ' ' << stats.TotalTime;
    fout.close();
}

void PrintStat(Statistics stats){
    // Print out statistics

    // derived statistics
    int TotalGames = stats.RussianWon + stats.RussianLost + stats.RussianDraw + stats.DemonWon + stats.DemonLost;
    int RussianGames = stats.RussianWon + stats.RussianLost + stats.RussianDraw;
    int DemonGames = stats.DemonWon + stats.DemonLost;

    cout << string(30, '\n');
    cout << "Statistics\n" << endl;
    cout << "Total game played: " << TotalGames << endl;
    
    cout << "Play count of Russian Dude level: " << RussianGames << endl;
    cout << "Russian Dude level won: " << stats.RussianWon << endl;
    cout << "Russian Dude level lost: " << stats.RussianLost << endl;
    cout << "Russian Dude level drawn: " << stats.RussianDraw << endl;

    // Handle exception caused by division by zero
    if (RussianGames == 0){
        cout << "Russian Dude level win %: " << "N/A" << endl;
    } else {
        cout << "Russian Dude level win %: " << (stats.RussianWon * 100 / RussianGames) << endl;
    }
    
    cout << "Play count of C++ Demon level: " << DemonGames << endl;
    cout << "C++ Demon level won: " << stats.DemonWon << endl;
    cout << "C++ Demon level lost: " << stats.DemonLost << endl;
    
    // Handle exception caused by division by zero
    if (DemonGames == 0){
        cout << "C++ Demon level win %: " << "N/A" << endl;
    } else {
        cout << "C++ Demon level win %: " << (stats.DemonWon * 100 / DemonGames) << endl;
    }
    
    cout << "Total time played: " << stats.TotalTime << " seconds" << endl;

    ReturnToMainMenu();
}
