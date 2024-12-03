#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <utility>
#include "ItemType.h"
#include "Entity.h"
#include "Shotgun.h"
#include <fstream>

class Entity;
class Shotgun;

class Item {
public:
    /// @brief Constructs an Item.
    /// @param type (ItemType) The type of the item.
    Item(ItemType type);

    /// @brief Returns the type of the item.
    /// @return (ItemType) The type of the item.
    ItemType getType();

    /// @brief Uses the item. Note that the item will not be removed from the Inventory. You have to call Inventory::resetSlot(int slot) if the item has been used successfully.
    /// @param user (Entity&) The entity who uses the item.
    /// @param target (Entity&) The target of the item usage.
    /// @param gun (Shotgun&) The current shotgun to be modified after using the item.
    /// @return (pair<bool, std::string>) Returns 1. Whether the item has been used successfully, and 2. The message after using the item.
    std::pair<bool, std::string> use(Entity& user, Entity& target, Shotgun& gun);

    /// @brief Default destructor.
    virtual ~Item() = default;

    void save(std::ofstream& fout) const;
    void load(std::ifstream& fin);

private:
    /// @brief The following variables should not be accessed from other .cpp files. Use the public functions instead.
    ItemType m_Type;
};

#endif //ITEM_H
