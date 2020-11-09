#ifndef CHARACTER_H
#define CHARACTER_H

#include "Definitions/CharacterDefinitions.h"
#include "Definitions/MapDefinitions.h"
#include "Definitions/TypeDefinitions.h"

#include <memory>
#include <string>
#include <vector>

#include <QImage>

class Armour;
class Weapon;

class Character
{
public:
    Character(int id,
              std::string name,
              std::vector<int> abilityScores,
              int health,
              std::vector<std::string> sprites);
    Character(int id,
              std::string name,
              std::vector<int> abilityScores,
              int health,
              std::shared_ptr<Armour> armour,
              std::shared_ptr<Weapon> weapon,
              Location location);
    ~Character();

    int GetID() const { return m_id; }

    std::string GetName() const { return m_name; }

    void SetAbilityScores(std::vector<int> abilityScores);
    int GetAbilityScore(CharacterDefinitions::AbilityEnum eAbility) const;

    void SetHealth(int health);
    int GetMaxHealth() const { return m_maxHealth; }
    int GetHealth() const { return m_health; }

    void SetArmour(std::shared_ptr<Armour> armour);
    std::shared_ptr<Armour> GetArmour() const { return m_armour; }

    void SetWeapon(std::shared_ptr<Weapon> weapon);
    std::shared_ptr<Weapon> GetWeapon() const { return m_weapon; }

    void UpdateArmourClass();
    int GetArmourClass() const { return m_armourClass; }

    Location GetOldLocation() const { return m_oldLocation; }
    Location GetLocation() const { return m_location; }
    void SetLocation(Location location);
    MapDefinitions::DirectionEnum GetDirection() const { return m_eDirection; }
    void SetDirection(MapDefinitions::DirectionEnum eDirection) { m_eDirection = eDirection; }

    QImage GetIdleSprite() {
        return m_sprites[m_eDirection - 1];
    }

    int GetAttack() const;
    int GetDamage() const;
    void TakeDamage(int damage);
    bool IsAlive() const { return m_health > 0; }

private:
    int m_id;
    std::string m_name;
    std::vector<int> m_abilityScores;
    int m_health;
    int m_maxHealth;
    int m_armourClass;

    std::shared_ptr<Armour> m_armour;
    std::shared_ptr<Weapon> m_weapon;

    std::shared_ptr<Armour> m_armourEmpty;
    std::shared_ptr<Weapon> m_weaponEmpty;

    std::pair<int,int> m_oldLocation;
    std::pair<int,int> m_location;
    MapDefinitions::DirectionEnum m_eDirection;

    std::vector<QImage> m_sprites;
};

#endif // CHARACTER_H
