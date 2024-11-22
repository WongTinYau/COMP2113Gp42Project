#ifndef STATS_H
#define STATS_H

struct Statistics{
    int TotalGamesPlay =0;
    int RussianWon =0;
    int RussianLosses =0;
    int DemonWin =0;
    int DemonLosses =0;
    int totalTimePlayed =0; //in seconds
};

void SaveStat(Statistics&stat);
void FindStat();
void hardReset();
void stats();
#endif // STATS_H
