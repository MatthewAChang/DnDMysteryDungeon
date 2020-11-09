#include "Treasure.h"

Treasure::Treasure(std::vector<std::shared_ptr<Item>> items,
                   MapDefinitions::DirectionEnum direction)
    : m_opened(false),
      m_items(items),
      m_direction(direction)
{
}

Treasure::~Treasure()
{
}
