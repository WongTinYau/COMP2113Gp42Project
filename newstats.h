#ifndef NEWSTATS_H_INCLUDED
#define NEWSTATS_H_INCLUDED

// save file = "data.txt"

struct Statistics{
    // statistics stored in file
    int RussianWon;
    int RussianLost;
    int DemonWon;
    int DemonLost;
    int TotalTime; //in seconds

    // derived statistics
    int TotalGames;
    int RussianGames;
    int DemonGames;

    //Constructor
    Statistics(int a, int b, int c, int d, int e){
        RussianWon = a;
        RussianLost = b;
        DemonWon = c;
        DemonLost = d;
        TotalTime = e;

        TotalGames = a + b + c + d;
        RussianGames = a + b;
        DemonGames = c + d;
    }
};

void InitializeStat(); // Create a new save file or reset current save
Statistics GetStat(); // Get statistics from file
void SaveStat(Statistics stats); // Write statistics into save file
void PrintStat(Statistics stats);


#endif // NEWSTATS_H_INCLUDED
