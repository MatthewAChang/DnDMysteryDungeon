#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

class Equipment: public Item
{
public:
    Equipment(std::string name, ItemDefinitions::ItemTypeEnum itemType) : Item(name, itemType) {}
    ~Equipment() {}
};

#endif // EQUIPMENT_H
