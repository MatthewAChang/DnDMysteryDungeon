#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <vector>
#include <string>

class Equipment
{
public:
    Equipment(std::string name);
    ~Equipment();

private:
    std::string m_name;
};

#endif // EQUIPMENT_H
