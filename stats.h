#ifndef STATS_H
#define STATS_H

struct Statistics{
    int TotalGamesPlay ;
    int RussianWon ;
    int RussianLosses ;
    int DemonWin ;
    int DemonLosses ;
    int totalTimePlayed ; //in seconds

    //Constructor
    Statistics(int a, int b, int c, int d, int e, int f){
        TotalGamesPlay = a;
        RussianWon = b;
        RussianLosses = c;
        DemonWin = d;
        DemonLosses = e;
        totalTimePlayed = f;
    }
};

void SaveStat(const Statistics&stat);
void FindStat();
void hardReset();
void stats();
void FairGame(Statistics&stat);
void updateRussianWin(Statistics&stat);
void updateRussianLost(Statistics&stat);
void updateDemonWin(Statistics&stat);
void updateDemonLost(Statistics&stat);
void TimeStat(Statistics&stat, time_t time);

#endif // STATS_H
