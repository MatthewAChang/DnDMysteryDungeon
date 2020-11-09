#include "Key.h"

Key::Key(std::string name, ItemDefinitions::KeyDoorTypeEnum type) :
    Item(name, ItemDefinitions::eKey),
    m_type(type)
{

}
