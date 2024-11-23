#ifndef NEWSTATS_H_INCLUDED
#define NEWSTATS_H_INCLUDED

// save file = "data.txt"

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

    //Constructor
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

void InitializeStat(); // Create a new save file or reset current save
Statistics GetStat(); // Get statistics from file
void SaveStat(Statistics stats); // Write statistics into save file
void PrintStat(Statistics stats);


#endif // NEWSTATS_H_INCLUDED
