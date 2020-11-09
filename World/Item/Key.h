#ifndef KEY_H
#define KEY_H

#include "Definitions/MapDefinitions.h"
#include "Item.h"

class Key: public Item
{
public:
    Key(std::string name, ItemDefinitions::KeyDoorTypeEnum type);
    ~Key() {}

    ItemDefinitions::KeyDoorTypeEnum GetType() const { return m_type; }

private:
    ItemDefinitions::KeyDoorTypeEnum m_type;
};

#endif // KEY_H
