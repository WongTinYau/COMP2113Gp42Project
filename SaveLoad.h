#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "GameState.h"

void SaveGame(const GameState& state);
bool LoadGame(GameState& state);

#endif // SAVELOAD_H
