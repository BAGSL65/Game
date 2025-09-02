#include "paras.h"

// 在这里定义地图长宽和贴图大小
const unsigned int BlockSize = 64;
const unsigned int MapLength = 8;
const unsigned int MapWidth = 6;
const float block_scale = 0.25f;
const float p_scale = 0.25f;
const float box_scale = 0.2f;
#ifdef RELEASE_BUILD
    const char * texture_path = "./resources/textures/";
    const char * mapdata_path = "./resources/maps/level_";
    const char * log_path = "./log/log.txt";
    const char* font_path = "./resources/font/chuchen.ttf";
    const char* title_font_path = "./resources/font/SuperVanilla.ttf";
    const char* music_path = "./resources/music/QuietMemory.wav";
    const char* sound_path = "./resources/sound/";
#else    
    const char * texture_path = "../../resources/textures/";
    const char * mapdata_path = "../../resources/maps/level_";
    const char * log_path = "../../log/log.txt";
    const char* font_path = "../../resources/font/chuchen.ttf";
    const char* title_font_path = "../../resources/font/SuperVanilla.ttf";
    const char* music_path = "../../resources/music/QuietMemory.wav";
    const char* sound_path = "../../resources/sound/";
#endif
    const char* tip_text[] = {
        "Tip: You are strong enough to push\n   the boxes by pressing the 'E' key", // 你是个壮汉，按E推箱子
        "Tip: Are you smart?", // 智慧是人类的财富
        "Tip: Water is a good friend", // 水能载舟
        "Tip: I hate the mud!", // 我讨厌泥！
        "Tip: Where is my light?", // 神说...光哪去了？
        "Tip: Rock and Roll baby!", // 摇滚我的宝贝！
        "Tip: Triple smash!", // 三重粉碎打击！
        "Tip:            is your friend...\n             NOT       !", // 红灯停，绿灯行！
        "Tip: Face the Challenge" // 干就完了
    };
    const int tip_text_scale[] = {
        20,25,25,25,25,25,25,20,25
    };
    const char* map_suffix = ".csv";