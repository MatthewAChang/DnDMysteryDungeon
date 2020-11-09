#ifndef DOOR_H
#define DOOR_H

#include "Definitions/MapDefinitions.h"
#include "Definitions/ItemDefinitions.h"
#include "Interactable.h"

class Item;

class Door: public Interactable
{
public:
    Door(ItemDefinitions::KeyDoorTypeEnum type,
         MapDefinitions::DirectionEnum direction);
    ~Door();

    bool IsOpened() const { return m_opened; }
    void Open() { m_opened = true; }
    void Close() { m_opened = false; }

    ItemDefinitions::KeyDoorTypeEnum GetType() const { return m_type; }
    MapDefinitions::DirectionEnum GetDirection() const { return m_direction; }

private:
    bool m_opened;

    ItemDefinitions::KeyDoorTypeEnum m_type;
    MapDefinitions::DirectionEnum m_direction;
};

#endif // DOOR_H
