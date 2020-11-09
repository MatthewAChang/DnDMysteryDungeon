#include "Potion.h"

Potion::Potion(std::string name, ItemDefinitions::PotionTypeEnum potionType) :
    Item(name, ItemDefinitions::ePotion),
    m_potionType(potionType)
{

}
