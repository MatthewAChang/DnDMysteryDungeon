#ifndef MAPDEFINITIONS_H
#define MAPDEFINITIONS_H

namespace MapDefinitions
{
    const int MAP_WIDTH = 1300;
    const int MAP_HEIGHT = 700;

    const int BLOCK_SIZE = 100;

    const int MAP_WIDTH_NUM = 13;
    const int MAP_HEIGHT_NUM = 7;

    const int LEVEL_MAP_EMPTY_ID = -1;
    const int LEVEL_MAP_PLAYER_ID = 0;

    enum LevelTerrainMapEnum { eWall = 0, eFloor };

    enum LevelInteractableMapEnum { eNone = 0, eTreasure, eDoor };

    enum DirectionEnum { eNull = 0, eWest, eNorth, eEast, eSouth };
}

#endif // MAPDEFINITIONS_H
