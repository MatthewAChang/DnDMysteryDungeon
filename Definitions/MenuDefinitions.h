#ifndef MENUDEFINITIONS_H
#define MENUDEFINITIONS_H

#include <QString>

namespace MenuDefinitions
{
    const QString SELECTED_FONT = "font-weight: bold; font-size: 35pt";
    const QString NOT_SELECTED_FONT = "font-weight: normal; font-size: 30pt";

    const QString START_TEXT = "START";
    const QString CONTINUE_TEXT = "CONTINUE";

    enum MenuItemEnum { eStart = 0, eExit };
}

#endif // MENUDEFINITIONS_H
