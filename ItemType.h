#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <string>

/// You should define your own custom items here.
enum class ItemType {
    SAW,
    MAGNIFYING_GLASS,
    INVERTER,
    HEART,
    HANDCUFF,
    MAGNET
};

/// @brief Returns the name of the item type.
/// @param type (ItemType) The type of the item.
/// @return (string) the name of the item type.
std::string toString(ItemType type);

#endif //ITEMTYPE_H