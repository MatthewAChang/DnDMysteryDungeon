#ifndef TREASURE_H
#define TREASURE_H

#include "Definitions/MapDefinitions.h"
#include "Interactable.h"

#include <memory>
#include <vector>

class Item;

class Treasure : public Interactable
{
public:
    Treasure(std::vector<std::shared_ptr<Item>> items,
             MapDefinitions::DirectionEnum direction);
    ~Treasure();

    bool GetOpened() const { return m_opened; }
    void Open() { m_opened = true; }
    void Close() { m_opened = false; }

    std::vector<std::shared_ptr<Item>> GetItems() const { return m_items; }
    void ClearItems() { m_items.clear(); }

    MapDefinitions::DirectionEnum GetDirection() const { return m_direction; }

private:
    bool m_opened;

    std::vector<std::shared_ptr<Item>> m_items;
    MapDefinitions::DirectionEnum m_direction;
};

#endif // TREASURE_H
