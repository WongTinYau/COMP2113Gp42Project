# COMP2113Gp42Project
## Team members
1. Wong Tin Yau (UID: 3036071304)
2. Lam Chun Hin (UID: 3036238433)
3. Leung Man Yan (UID: 3036239279)
4. Hung Lim Fung (UID: 3036227745)
5. Yuen Lap Ming (UID: 3036222939)

## About this game
### Title: New Russian Roulette

### DEMO:
(TBA)

### Introduction
Have you heard of Russian Roulette? Instead of the original real-life death game,
New Russian Roulette is the game version of it, with multiple lives to spare and items 
to allow strategic play.

You will fight against the AI player (referred as Dealer in-game).

This game is also heavily inspired by the game Buckshot Roulette.

### Game rules
Basically, each player may use any number of items, then decide to shoot himself or the opponent.
However, shots can be either empty or full, the items each player receive is also randomized.
You win if the opponent dies (live total <= 0).
Due to complex item & phase interactions, instead of listing them here (which will take > 50 lines), 
we will recommend learning the details via gameplay.
Please refer to help.cpp (source code documentation) 
or the help menu (in-game documentation) for details.

### Libraries used
Only standard C/C++ libraries are used.

## Compilation and execution
(TBA)

## Code requirements
1.	Generation of random event: Random bullet initialization, Random item allocation
2.	Data structure for storing data: (TBA)
3.	Dynamic memory management: (TBA)
4.	File I/O: Separate txt file to store game statistics
5.	Program codes in multiple files: This project contains ~20 files

## Creative and fun elements
1.	Level selection: Russian Dude, C++ Demon
2.	Storyline: ideally achieved by playing Rissian Dude level first (and win it), then C++ Demon level
3.	ASCII Art!

## FAQ
Q: What is the difference between the 2 levels?
A: Quite a lot, in general C++ Demon level should be harder to beat. 
    1. AI in C++ Demon level is smarter
    2. The C++ Demon has a way higher life total than Russian Dude
    3. More shots per reload, hence making probability calculations a bit harder for players
    Besides difference in difficulty, C++ Demon level only ends when one of the layer dies,
    while Russian Dude level ends as soon as there are no shot left.

Q: Are those arts original?
A: 'Not completely, either modified from online sources manually or used AI-tools to generate.' ~ Wong Tin Yau