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
Click [here](https://connecthkuhk-my.sharepoint.com/personal/u3622293_connect_hku_hk/_layouts/15/stream.aspx?id=%2Fpersonal%2Fu3622293%5Fconnect%5Fhku%5Fhk%2FDocuments%2Fdemo%202%2E0%2Emp4&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&ga=1&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2E2cd172de%2D6ca9%2D44e6%2D8cb6%2Dff8b86355a99)

### Introduction
Have you heard of Russian Roulette? Instead of the original real-life death game,
New Russian Roulette is the text-based game version of it, with multiple lives for players to spare 
and items to allow strategic play.

You will fight against the AI player (referred as Dealer in-game).

This game is also heavily inspired by the game Buckshot Roulette.

### Game rules
Basically, each player may use any number of items, then decide to shoot himself or the opponent.

However, shots can be either empty or full, the items each player receive are also randomized.

You win if the opponent dies (live total <= 0).

> [!IMPORTANT]
> When entering commands, please refer strictly to the character indicated, and exclude ().

Due to complex item & phase interactions, instead of listing them here (which will take > 50 lines), 
we will recommend learning the details via gameplay.

> [!TIP]
> For more information, please refer to 
> * help.cpp (source code documentation)
> * The Help menu (in-game documentation)

### Libraries used
Only standard C/C++ libraries are used.

## Compilation and execution
It is an easy 2-step process due to Makefile
1. Type 'make'
2. Type './game'

Ignore those 'warning: comparison of integer expression with different signedness' lines,
the game is perfectly functional.

## Code requirements
1.	Generation of random event: Random bullet initialization, Random item allocation
2.	Data structure for storing data:
    * struct Gamestate: store game status for loading an unfinished game
    * struct Statistics: store various game statistics (e.g. win rate, play time)
3.	Dynamic memory management: The following objects are dynamically generated upon entering a level
    * class Shotgun shotgun
    * class Entity player
    * class Entity dealer
4.	File I/O: Separate txt files to store game data
    * data.txt: store game statistics
    * savegame.dat: store unfinished game
5.	Program codes in multiple files: This project contains ~30 files in total

## Creative and fun elements
1.	Level selection: Russian Dude, C++ Demon, Vanilla mode
2.	Storyline: ideally achieved by playing Rissian Dude level first (and win it), then C++ Demon level
3.	ASCII Art!
    * Background color change when a level is beaten for at least once
    * ASCII pictures in cutscenes

## FAQ
Q: What are the differences between Russian Dude level and C++ Demon level?

A: Quite a lot. 
1. In general, C++ Demon level should be harder to beat.
    - AI in C++ Demon level is smarter
    - The C++ Demon has a way higher life total than Russian Dude
    - More shots per reload, hence making probability calculations a bit harder for players
2. Different game end conditions.
    - C++ Demon level: ends when one of the layer dies
    - Russian Dude level: ends as soon as there are no shot left, possible to end in a draw

Q: What is vanilla mode?

A: It is Russian Dude level but without items, an attempt to simulate real life russian roulette.

Q: Are those arts original?

A: Not completely, they are either manually modified from online sources or generated by AI-tools.