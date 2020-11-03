#ifndef ARMOURDEFINITIONS_H
#define ARMOURDEFINITIONS_H

#include <vector>
#include <string>

namespace ArmourDefinitions
{
    enum ArmourEnum { eNone = 0, ePadded, eLeather, eStuddedLeather, eHide, eChainShirt, eScaleMail, eBreastPlate, eHalfPlate, eRingMail, eChainMail, eSplint, ePlate};

    enum ArmourTypeEnum { eLightArmour = 0, eMediumArmour, eHeavyArmour, eNaturalArmour};

    const std::vector<std::string> ARMOUR_NAME = {
        "None",
        "Padded",
        "Leather",
        "Studded Leather",
        "Hide",
        "Chain Shirt",
        "Scale Mail",
        "Breast Plate",
        "Half Plate",
        "Ring Mail",
        "Chain Mail",
        "Splint",
        "Plate",
    };

    const std::vector<int> ARMOUR_CLASS_BASE = {
        0,
        11,
        11,
        12,
        12,
        13,
        14,
        14,
        15,
        14,
        16,
        17,
        18
    };

    const std::vector<ArmourTypeEnum> ARMOUR_TYPE = {
        eLightArmour,
        eLightArmour,
        eLightArmour,
        eLightArmour,
        eMediumArmour,
        eMediumArmour,
        eMediumArmour,
        eMediumArmour,
        eMediumArmour,
        eHeavyArmour,
        eHeavyArmour,
        eHeavyArmour,
        eHeavyArmour,
    };

    const std::vector<int> ARMOUR_MIN_STRENGTH = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        13,
        15,
        15,
    };
}

#endif // ARMOURDEFINITIONS_H
