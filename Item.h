#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <utility>
#include <random>
#include "ItemType.h"
#include "Entity.h"
#include "Shotgun.h"

class Item {
public:
    Item(ItemType type);
    ItemType getType();
    std::pair<bool, string> use(Entity& user, Entity& target, Shotgun& gun);
    virtual ~Item() = default;

private:
    ItemType m_Type;
};

#endif //ITEM_H