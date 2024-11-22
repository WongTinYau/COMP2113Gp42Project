#ifndef STATS_H
#define STATS_H

struct Statistics{
    int TotalGamesPlay ;
    int RussianWon ;
    int RussianLosses ;
    int DemonWin ;
    int DemonLosses ;
    int totalTimePlayed ; //in seconds
};

Statistics stat ={0,0,0,0,0,0};

void SaveStat(Statistics&stat);
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
