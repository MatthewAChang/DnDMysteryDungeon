#include "PlayerGenerator.h"
#include "Definitions/PlayerDefinitions.h"

#include "EquipmentGenerator.h"
#include "Helper/Helper.h"
#include "World/Characters/Player.h"

#include "assert.h"

using namespace PlayerDefinitions;

PlayerGenerator::PlayerGenerator() : m_equipmentGenerator(std::make_unique<EquipmentGenerator>())
{
}

PlayerGenerator::~PlayerGenerator()
{
}

std::shared_ptr<Player> PlayerGenerator::GeneratePlayer(std::string name, ClassEnum eClass, RaceEnum eRace)
{
    using namespace CharacterDefinitions;

    std::vector<int> abilityScores(6, 0);

    abilityScores[eStrength] += RACE_ABILITY_SCORE[eRace][eStrength] + CLASS_ABILITY_SCORE[eClass][eStrength];
    abilityScores[eDexterity] += RACE_ABILITY_SCORE[eRace][eDexterity] + CLASS_ABILITY_SCORE[eClass][eDexterity];
    abilityScores[eConstitution] += RACE_ABILITY_SCORE[eRace][eConstitution] + CLASS_ABILITY_SCORE[eClass][eConstitution];
    abilityScores[eIntelligence] += RACE_ABILITY_SCORE[eRace][eIntelligence] + CLASS_ABILITY_SCORE[eClass][eIntelligence];
    abilityScores[eWisdom] += RACE_ABILITY_SCORE[eRace][eWisdom] + CLASS_ABILITY_SCORE[eClass][eWisdom];
    abilityScores[eCharisma] += RACE_ABILITY_SCORE[eRace][eCharisma] + CLASS_ABILITY_SCORE[eClass][eCharisma];

    auto player = std::make_shared<Player>(0,
                                           name,
                                           eClass,
                                           eRace,
                                           abilityScores,
                                           BASE_HEALTH[eClass] + Helper::GetInstance().GetAbilityScoreModifier(abilityScores[eConstitution]),
                                           SPRITES);

    GenerateEquipment(player);

    return player;
}

void PlayerGenerator::GenerateEquipment(std::shared_ptr<Player>& player)
{
    switch(player->GetClass())
    {
    case eBarbarian:
        player->SetArmour(m_equipmentGenerator->GenerateArmour(ArmourDefinitions::eHide));
        player->SetWeapon(m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eGreataxe));

        m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eJavelin);

        break;
    case eFighter:
        player->SetArmour(m_equipmentGenerator->GenerateArmour(ArmourDefinitions::eChainMail));
        player->SetWeapon(m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eLongsword));

        m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eLightCrossbow);

        break;
    case eRogue:
        player->SetArmour(m_equipmentGenerator->GenerateArmour(ArmourDefinitions::eLeather));
        player->SetWeapon(m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eShortsword));

        m_equipmentGenerator->GenerateWeapon(WeaponDefinitions::eShortbow);

        break;
    default:
        assert(false);
    }
}
