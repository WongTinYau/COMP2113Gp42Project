#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <string>

enum class ItemType {
    SAW,
    MAGNIFYING_GLASS,
    INVERTER,
    HEART,
    HANDCUFF,
    MAGNET
};

std::string toString(ItemType type);

#endif //ITEMTYPE_H