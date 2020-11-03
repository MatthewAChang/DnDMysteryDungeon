#ifndef MAPDEFINITIONS_H
#define MAPDEFINITIONS_H

namespace MapDefinitions
{
    const int MAP_WIDTH = 1300;
    const int MAP_HEIGHT = 700;

    const int BLOCK_SIZE = 100;

    const int MAP_WIDTH_NUM = 13;
    const int MAP_HEIGHT_NUM = 7;

    enum LevelTerrainMapEnum { eWall = 0, eFloor };

    enum LevelCharacterMapEnum { eEmpty = -1, ePlayer = 0, eEnemy = 1 };
}

#endif // MAPDEFINITIONS_H
