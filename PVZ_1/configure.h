#ifndef CONFIGURE_H
#define CONFIGURE_H

/*刷新时间*/
#define Refresh_Time 50//msec

#define SCENE_WIDTH 920
#define SCENE_HEIGHT 606

/*自定义QGraphicsItem的类型Type*/
#define ZOMBIE 1
#define PLANT 2
#define MAP 3
#define STORE 4
#define SUN 5
#define PLANTCARD 6
#define BULLET 7

/*僵尸状态*/
#define ZombieWalk 1
#define ZombieEat 2
#define ZombieDead 3

#define Grid_Width 80
#define Grid_Heigt 98

enum PlantType
{
    PEASHOOTER,
    REPEATER,
    SNOWPEA,
    WALLNUT,
    TALLNUT,
    SQUASH,
    CHERRYBOMB,
    GARLIC,
    SUNFLOWER
};

enum ZombieType {
    NORMAL_ZOMBIE,POLE_ZOMBIE, CONEHEAD_ZOMBIE, NEWSPAPER_ZOMBIE,   BOX_ZOMBIE, CATAPULT_ZOMBIE
};
#endif // CONFIGURE_H


