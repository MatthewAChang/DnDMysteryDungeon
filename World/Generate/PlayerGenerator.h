#ifndef GENERATEPLAYER_H
#define GENERATEPLAYER_H

#include "Definitions/PlayerDefinitions.h"

#include <memory>
#include <string>

class EquipmentGenerator;
class Player;

class PlayerGenerator
{
public:
    PlayerGenerator();
    ~PlayerGenerator();

    std::shared_ptr<Player> GeneratePlayer(std::string name,
                                           PlayerDefinitions::ClassEnum eClass,
                                           PlayerDefinitions::RaceEnum eRace);

private:
    void GenerateEquipment(std::shared_ptr<Player>& player);

    std::unique_ptr<EquipmentGenerator> m_equipmentGenerator;
};

#endif // GENERATEPLAYER_H
