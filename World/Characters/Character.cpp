#include "Character.h"

#include "Helper/Helper.h"
#include "World/Generate/EquipmentGenerator.h"
#include "World/Item/Armour.h"
#include "World/Item/Weapon.h"
#include "Definitions/WeaponDefinitions.h"

#include <algorithm>

using namespace CharacterDefinitions;

Character::Character(int id,
                     std::string name,
                     std::vector<int> abilityScores,
                     int health,
                     std::vector<std::string> sprites) :
    m_id(id),
    m_name(name),
    m_abilityScores(abilityScores),
    m_health(health),
    m_maxHealth(health),
    m_armourClass(0),
    m_armour(nullptr),
    m_weapon(nullptr),
    m_armourEmpty(),
    m_weaponEmpty(),
    m_oldLocation({0, 0}),
    m_location({0, 0}),
    m_eDirection(MapDefinitions::eWest)
{
    for (const auto& sprite : sprites)
    {
        m_sprites.push_back(QImage(QString::fromStdString("..\\DnDMysteryDungeon\\Images\\" + sprite)));
    }

    auto equipmentGenerator = std::make_unique<EquipmentGenerator>();

    m_armourEmpty = equipmentGenerator->GenerateArmour(ArmourDefinitions::eNone);
    m_weaponEmpty = equipmentGenerator->GenerateWeapon(WeaponDefinitions::eNone);

    m_armour = m_armourEmpty;
    m_weapon = m_weaponEmpty;

    UpdateArmourClass();
}

Character::Character(int id,
                     std::string name,
                     std::vector<int> abilityScores,
                     int health,
                     std::shared_ptr<Armour> armour,
                     std::shared_ptr<Weapon> weapon,
                     Location location) :
    m_id(id),
    m_name(name),
    m_abilityScores(abilityScores),
    m_health(health),
    m_maxHealth(health),
    m_armourClass(0),
    m_armour(armour),
    m_weapon(weapon),
    m_oldLocation(location),
    m_location(location),
    m_eDirection(MapDefinitions::eWest)
{
    UpdateArmourClass();
}

Character::~Character()
{
}

void Character::SetAbilityScores(std::vector<int> abilityScores)
{
    m_abilityScores = abilityScores;
    UpdateArmourClass();
}

int Character::GetAbilityScore(AbilityEnum eAbility) const
{
    return m_abilityScores[eAbility];
}

void Character::SetHealth(int health)
{
    m_health = health;
    m_maxHealth = health;
}

void Character::SetArmour(std::shared_ptr<Armour> armour)
{
    if (armour)
    {
        m_armour = armour;
    }
    else
    {
        m_armour = m_armourEmpty;
    }
    UpdateArmourClass();
}

void Character::SetWeapon(std::shared_ptr<Weapon> weapon)
{
    if (weapon)
    {
        m_weapon = weapon;
    }
    else
    {
        m_weapon = m_weaponEmpty;
    }
}

void Character::UpdateArmourClass()
{
    m_armourClass = m_armour->GetArmourClassBase() +
                    std::min(m_armour->GetMaxDexBonus(),
                             Helper::GetInstance().GetAbilityScoreModifier(m_abilityScores[eDexterity]));
}

void Character::SetLocation(Location location)
{
    m_oldLocation = m_location;
    m_location = location;
}

int Character::GetAttack() const
{
    return (rand() % 20 + 1) + Helper::GetInstance().GetAbilityScoreModifier(m_abilityScores[m_weapon->GetAbiltyModifier()]) + 2;
}

int Character::GetDamage() const
{
    return m_weapon->GetDamage() + Helper::GetInstance().GetAbilityScoreModifier(m_abilityScores[m_weapon->GetAbiltyModifier()]);
}

void Character::TakeDamage(int damage)
{
    m_health -= damage;
}

