#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include "Shell.h"
#include "Shotgun.h"

using namespace std;

//The shotgun is loaded upon initialization. You can write a reload function if you want.
Shotgun::Shotgun(int liveCount, int maxStock, int damage) {
    m_damage = damage;
    for (int i = 0; i < maxStock; ++i) {
        if (liveCount > 0) {
            m_shotgun.push_back(Shell::LIVE);
            --liveCount;
        } else {
            m_shotgun.push_back(Shell::BLANK);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(m_shotgun.begin(), m_shotgun.end(), g);
}

int Shotgun::getRemainingLiveShells() {
    return count(m_shotgun.begin(), m_shotgun.end(), Shell::LIVE);
}

int Shotgun::getRemainingShells() {
    return m_shotgun.size();
}

bool Shotgun::isEmpty() {
    return m_shotgun.empty();
}

pair<Shell, int> Shotgun::shoot() {
    Shell shell = m_shotgun.back();
    m_shotgun.pop_back();
    int final_damage = getUpcomingDamage();
    m_tempDamage = 0;
    return make_pair(shell, final_damage);
}

void Shotgun::increaseTempDamage(int tempDamage) {
    m_tempDamage += tempDamage;
}

int Shotgun::getUpcomingDamage() {
    int finalDamage = m_damage + m_tempDamage;
    return finalDamage;
}

Shell Shotgun::getUpcomingShell() {
    return m_shotgun.back();
}

void Shotgun::invertUpcomingShell() {
    if(m_shotgun.back() == Shell::BLANK) {
        m_shotgun.back() = Shell::LIVE;
    }
    else if(m_shotgun.back() == Shell::LIVE) {
        m_shotgun.back() = Shell::BLANK;
    }
}