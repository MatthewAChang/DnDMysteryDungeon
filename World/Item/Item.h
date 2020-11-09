#ifndef ITEM_H
#define ITEM_H

#include "Definitions/ItemDefinitions.h"

#include <string>

class Item
{
public:
    Item(std::string name, ItemDefinitions::ItemTypeEnum itemType);
    virtual ~Item() {}

    std::string GetName() const { return m_name; }
    ItemDefinitions::ItemTypeEnum GetItemType() const { return m_itemType;}

private:
    std::string m_name;
    ItemDefinitions::ItemTypeEnum m_itemType;
};

#endif // ITEM_H
