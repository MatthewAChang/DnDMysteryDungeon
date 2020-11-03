#ifndef CHARACTERDEFINITIONS_H
#define CHARACTERDEFINITIONS_H

namespace CharacterDefinitions
{
    enum AbilityEnum { eStrength = 0, eDexterity, eConstitution, eIntelligence, eWisdom, eCharisma };

    enum DirectionEnum { eNull = 0, eWest, eNorth, eEast, eSouth };

    enum EnemyStateEnum { eIdle = 0, eGuard, eAggro };
}

#endif // CHARACTERDEFINITIONS_H
