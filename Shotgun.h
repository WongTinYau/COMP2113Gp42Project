#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <vector>
#include <utility>
#include "Shell.h"

class Shotgun {
public:
    /// @brief Constructs a shotgun.
    /// @param liveCount (int) The amount of live shells of the shotgun.
    /// @param maxStock  (int) The maximum number of shells of the shotgun.
    /// @param damage  (int) The amount of base damage of the shotgun (The amount of lives deducted after shooting if the upcoming shell is live).
    Shotgun(int liveCount, int maxStock, int baseDamage);

    /// @brief Returns the remaining live shells of the shotgun.
    /// @return (int) The remaining live shells of the shotgun.
    int getRemainingLiveShells();

    /// @brief Returns the remaining shells (both live and blank) of the shotgun.
    /// @return (int) The remaining shells (both live and blank) of the shotgun.
    int getRemainingShells();

    /// @brief Returns whether the shotgun is empty.
    /// @return (bool) Whether the shotgun is empty.
    bool isEmpty();

    /// @brief Fires the shotgun.
    /// @return (pair<Shell, int>) Returns 1. The current shell (live or blank), and 2. The final number of lives to be deducted to the target.
    std::pair<Shell, int> shoot();
    
    /// @brief Increases the extra damage of the shotgun (Extra lives to be deducted to the target after shooting). Note that the extra damage will be reset to 0 no matter what the upcoming shell is.
    /// @param damage (int) The amount of extra damage of the shotgun (Extra lives to be deducted to the target after shooting).
    void increaseTempDamage(int damage);

    /// @brief Returns the upcoming damage after accounting for the extra damage (The amount of lives to be deducted after shooting if the upcoming shell is live).
    /// @return (int) The upcoming damage after accounting for the extra damage (The amount of lives to be deducted after shooting if the upcoming shell is live).
    int getUpcomingDamage();

    /// @brief Returns the upcoming shell of the shotgun.
    /// @return (Shell) The upcoming shell of the shotgun.
    Shell getUpcomingShell();

    /// @brief Inverts the upcoming shell of the shotgun (Blank -> Live; Live -> Blank).
    void invertUpcomingShell();

    /// @brief Default destructor.
    virtual ~Shotgun() = default;

private:
    /// @brief The following variables should not be accessed from other .cpp files. Use the public functions instead.
    std::vector<Shell> m_shotgun;
    int m_baseDamage;
    int m_damage;
    int m_tempDamage = 0;
};
#endif //SHOTGUN_H