#ifndef STATE_ENUM_H
#define STATE_ENUM_H
enum class MoveState {
    Idle
};
enum class LevelState {
    LEVEL0 = 0,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL7,
    LEVEL8
};
enum class GameState 
{
    StartMenu=0,
    Loading=1,
    Playing=2,
    Paused=3,
    LevelPassing=4,
    Config=5,
    GameFinish=6

};
enum class SoundName{
    EnterMenu,
    Footstep,
    PushBox,
    PushBoxCantmove,
    SwitchMenu
};

enum class TextureName {
    Exit=0,
    Water=1,
    Box=2,
    Grass=3,
    Pupu=5,
    Wall_Corner_Top_Left=10,
    Wall_Corner_Top_Right=11,
    Wall_Corner_Bottom_Left=12,
    Wall_Corner_Bottom_Right=13,

    Wall_Border_Left=20,
    Wall_Border_Right=21,
    Wall_Border_Top=22,
    Wall_Border_Bottom=23,
    Wall_Border_Horizontal=24,
    Wall_Border_Vertical=25,

    Wall_Convex_Left=30,
    Wall_Convex_Right=31,
    Wall_Convex_Top=32,
    Wall_Convex_Bottom=33,

    Wall_Block=40
};
#endif