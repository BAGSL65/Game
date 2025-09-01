#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "loader.h"
#include <fstream>
#include "paras.h"
sf::Texture load_texture(const char * filename){
    char * path_full = new char[strlen(texture_path) + strlen(filename) + 1];
    path_full = strcpy(path_full, texture_path);
    path_full = strcat(path_full, filename);
    std::ifstream file(path_full);
    sf::Texture t;
    if (!file.is_open())
    {
        throw LoadException("Failed to open texture file");
    }
    if(!t.loadFromFile(path_full)) 
    {
        // 错误处理
        throw LoadException("Failed to load texture");
    }
    delete [] path_full;
    return t;
}

sf::SoundBuffer load_sound(const char * filename){
    char * path_full = new char[strlen(sound_path) + strlen(filename) + 1];
    path_full = strcpy(path_full, sound_path);
    path_full = strcat(path_full, filename);
    std::ifstream file(path_full);
    sf::SoundBuffer t;
    if (!file.is_open())
    {
        throw LoadException("Failed to open sound file");
    }
    if(!t.loadFromFile(path_full)) 
    {
        // 错误处理
        throw LoadException("Failed to load sound");
    }
    delete [] path_full;
    return t;
}
void load_texture(std::unordered_map<TextureName,sf::Texture>& texture_map) {

        // wall-block
        sf::Texture wall_block = load_texture("Wall_Inside.png");
        texture_map[TextureName::Wall_Block] = wall_block;
        // wall-border
        sf::Texture wall_b_l = load_texture("Wall_Border_Left.png");
        texture_map[TextureName::Wall_Border_Left] = wall_b_l;
        sf::Texture wall_b_r = load_texture("Wall_Border_Right.png");
        texture_map[TextureName::Wall_Border_Right] = wall_b_r;
        sf::Texture wall_b_u = load_texture("Wall_Border_Up.png");
        texture_map[TextureName::Wall_Border_Top] = wall_b_u;
        sf::Texture wall_b_d = load_texture("Wall_Border_Down.png");
        texture_map[TextureName::Wall_Border_Bottom] = wall_b_d;
        sf::Texture wall_d_b_h = load_texture("Wall_Double_Border_Horizontal.png");
        texture_map[TextureName::Wall_Border_Horizontal] = wall_d_b_h;
        sf::Texture wall_d_b_v = load_texture("Wall_Double_Border_Vertical.png");
        texture_map[TextureName::Wall_Border_Vertical] = wall_d_b_v;
        // wall-convex
        sf::Texture wall_convex_l = load_texture("Wall_Convex_Left.png");
        texture_map[TextureName::Wall_Convex_Left] = wall_convex_l;
        sf::Texture wall_convex_r = load_texture("Wall_Convex_Right.png");
        texture_map[TextureName::Wall_Convex_Right] = wall_convex_r;
        sf::Texture wall_convex_u = load_texture("Wall_Convex_Up.png");
        texture_map[TextureName::Wall_Convex_Top] = wall_convex_u;
        sf::Texture wall_convex_d = load_texture("Wall_Convex_Down.png");
        texture_map[TextureName::Wall_Convex_Bottom] = wall_convex_d;
        // wall-corner
        sf::Texture wall_corner_dl = load_texture("Wall_Corner_Down_Left.png");
        texture_map[TextureName::Wall_Corner_Bottom_Left] = wall_corner_dl;
        sf::Texture wall_corner_dr = load_texture("Wall_Corner_Down_Right.png");
        texture_map[TextureName::Wall_Corner_Bottom_Right] = wall_corner_dr;
        sf::Texture wall_corner_ul = load_texture("Wall_Corner_Up_Left.png");
        texture_map[TextureName::Wall_Corner_Top_Left] = wall_corner_ul;
        sf::Texture wall_corner_ur = load_texture("Wall_Corner_Up_Right.png");
        texture_map[TextureName::Wall_Corner_Top_Right] = wall_corner_ur;
        // water
        sf::Texture water = load_texture("Water.png");
        texture_map[TextureName::Water] = water;
        // grass
        sf::Texture grass = load_texture("Grass.png");
        texture_map[TextureName::Grass] = grass;
        // box
        sf::Texture box = load_texture("Box.png");
        texture_map[TextureName::Box] = box;
        // Pupu
        sf::Texture pupu = load_texture("Pupu.png");
        texture_map[TextureName::Pupu] = pupu;
        // Exit
        texture_map[TextureName::Exit] = grass;
}

void load_sound_map(std::unordered_map<SoundName,sf::SoundBuffer>& soundBufferMap,std::unordered_map<SoundName,std::shared_ptr<sf::Sound>>& soundMap) {
        
    soundBufferMap[SoundName::EnterMenu] = load_sound("EnterMenu.wav");
    soundBufferMap[SoundName::Footstep] = load_sound("Footstep.wav");
    soundBufferMap[SoundName::PushBox] = load_sound("PushBox.wav");
    soundBufferMap[SoundName::PushBoxCantmove] = load_sound("PushBoxCantMove.wav");
    soundBufferMap[SoundName::SwitchMenu] = load_sound("SwitchMenu.wav");
    
    soundMap[SoundName::EnterMenu] = std::make_shared<sf::Sound>(soundBufferMap[SoundName::EnterMenu]);
    soundMap[SoundName::SwitchMenu] = std::make_shared<sf::Sound>(soundBufferMap[SoundName::SwitchMenu]);
    soundMap[SoundName::Footstep] = std::make_shared<sf::Sound>(soundBufferMap[SoundName::Footstep]);
    soundMap[SoundName::PushBox] = std::make_shared<sf::Sound>(soundBufferMap[SoundName::PushBox]);
    soundMap[SoundName::PushBoxCantmove] = std::make_shared<sf::Sound>(soundBufferMap[SoundName::PushBoxCantmove]);
}