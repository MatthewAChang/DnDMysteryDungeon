#include "Door.h"

Door::Door(ItemDefinitions::KeyDoorTypeEnum type,
           MapDefinitions::DirectionEnum direction)
    : m_opened(false),
      m_type(type),
      m_direction(direction)
{
}

Door::~Door()
{
}
