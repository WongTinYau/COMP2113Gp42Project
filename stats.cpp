#include<iostream>
#include<string>
#include <fstream>
#include"stats.h"
#include"main.h"
using namespace std;

void SaveStat(const Statistics&stat){
    ofstream fout("stat.txt");
    fout<< "Total Game Played:"<<stat.TotalGamesPlay<<"\n";
    fout<<"Russian Dude mode"<<"\n";
    fout<<"Won: "<<stat.RussianWon<<"\n";
    fout<<"Losses: "<<stat.RussianLosses<<"\n";
    fout<<"Demon mode"<<"\n";
    fout<<"Wins: "<<stat.DemonWin<<"\n";
    fout<<"Losses"<<stat.DemonLosses<<"\n";
    fout<<"Winning percentage (Russian Dude Mode): "<<(stat.RussianWon/stat.TotalGamesPlay*100)<<"%"<<"\n";
    fout<<"Losing percentage (Russian Dude mode): "<<(stat.RussianLosses/stat.TotalGamesPlay*100)<<"%"<<"\n";
    fout<<"Winning percentage (Russian Dude Mode): "<<(stat.DemonWin/stat.TotalGamesPlay*100)<<"%"<<"\n";
    fout<<"Losing percentage (Russian Dude Mode): "<<(stat.DemonLosses/stat.TotalGamesPlay*100)<<"%"<<"\n";
    fout<<"Total TIme played: "<<(stat.totalTimePlayed/3600)<<"hour"<<(stat.totalTimePlayed/60)<<"minutes"<<"\n";
    fout.close();
}

void FindStat(){
    ifstream fin("stat.txt");
    string line;
    while (getline(fin,line)){
        cout<<line<<endl;
    }
}

void hardReset(){
    ofstream file("stat.txt",ofstream::trunc);
    cout<<"All Stats and save data have been reset.";
}

void FairGame(Statistics&stat){
    stat.TotalGamesPlay++;
}

void updateRussianWin(Statistics&stat){
    stat.TotalGamesPlay++;
    stat.RussianWon++;
    SaveStat(stat);
}

void updateRussianLost(Statistics&stat){
    stat.TotalGamesPlay++;
    stat.RussianLosses++;
    SaveStat(stat);
}

void updateDemonWin(Statistics&stat){
    stat.TotalGamesPlay++;
    stat.DemonWin++;
    SaveStat(stat);
}

void updateDemonLost(Statistics&stat){
    stat.TotalGamesPlay++;
    stat.DemonLosses++;
    SaveStat(stat);
}

void TimeStat(Statistics&stat, time_t time){
    time_t endtime = std::time(nullptr);
    int Timeplay =static_cast <int> (endtime-time);
    stat.totalTimePlayed+=Timeplay;
    SaveStat(stat);
}

void stats(){
    cout << "Game Statstics" << endl;
    FindStat();
    // TBA
    string Input;
    cout << "Enter any key to return to main menu" << endl;
    cin >> Input;
    main_menu();
}
