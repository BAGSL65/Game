#include "paras.h"

// 在这里定义地图长宽和贴图大小
const unsigned int BlockSize = 64;
const unsigned int MapLength = 8;
const unsigned int MapWidth = 6;
const float block_scale = 0.25f;
const float p_scale = 0.25f;
const float box_scale = 0.2f;
const unsigned int player_ini_pos_x = 1;
const unsigned int player_ini_pos_y = 2;
#ifdef RELEASE_BUILD
    const char * texture_path = "./resources/textures/";
    const char * mapdata_path = "./resources/maps/level001.csv";
    const char * log_path = "./log/log.txt";
#else    
    const char * texture_path = "../../resources/textures/";
    const char * mapdata_path = "../../resources/maps/level001.csv";
    const char * log_path = "../../log/log.txt";
#endif