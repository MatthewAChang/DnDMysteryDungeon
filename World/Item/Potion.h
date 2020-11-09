#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion: public Item
{
public:
    Potion(std::string name, ItemDefinitions::PotionTypeEnum potionType);
    ~Potion() {}

    ItemDefinitions::PotionTypeEnum GetPotionType() const { return m_potionType; }

private:
    ItemDefinitions::PotionTypeEnum m_potionType;
};

#endif // POTION_H
