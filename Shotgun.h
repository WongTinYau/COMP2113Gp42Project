#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <vector>
#include <algorithm>
#include <random>
#include "Shell.h"

class Shotgun {
public:
    Shotgun(int liveCount, int maxStock, int damage);
    int getRemainingLiveShells();
    int getRemainingShells();
    bool isEmpty();
    Shell shoot();
    void increaseTempDamage(int damage);
    int getUpcomingDamage();
    Shell getUpcomingShell();
    void invertUpcomingShell();
    virtual ~Shotgun() = default;

private:
    std::vector<Shell> m_shotgun;
    int m_damage;
    int m_tempDamage = 0;
};
#endif //SHOTGUN_H