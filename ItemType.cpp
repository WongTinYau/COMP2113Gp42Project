#include <string>
#include "ItemType.h"

std::string toString(ItemType type) {
    switch (type) {
        case ItemType::SAW: return "Saw";
        case ItemType::MAGNIFYING_GLASS: return "Magnifying Glass";
        case ItemType::INVERTER: return "Inverter";
        case ItemType::HEART: return "Heart";
        case ItemType::HANDCUFF: return "Handcuff";
        case ItemType::MAGNET: return "Magnet";
        default: return "Unknown";
    }
}