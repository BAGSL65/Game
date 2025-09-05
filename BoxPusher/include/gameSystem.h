#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include <SFML/Audio.hpp>

#include "box.h"
#include "player.h"
#include "water.h"
#include "mapLoader.h"
#include "stateEnum.h"
#include "loader.h"
#include "common_tool.h"
#include "logger.h"

extern Logger logger;
extern GameState gameState;
extern LevelState level;
extern bool isLevelInited;
extern bool isLoadTextInited;
extern bool isPauseScreenInited;

extern std::vector<std::vector<sf::Sprite>> sBlockList2d;
extern std::vector<sf::FloatRect> sBlockBoundsList;
// Using Autoptr for safety
extern std::vector<std::shared_ptr<Water>> waterList;
extern std::vector<std::shared_ptr<Box>> boxList;
extern std::unordered_map<float, std::shared_ptr<Water>> waterMap;
extern std::unordered_map<float, std::shared_ptr<Box>> boxMap;

extern std::vector<std::vector<int>> mapData;
extern std::unordered_map<TextureName, sf::Texture> texture_map;
extern sf::RenderTexture renderTexture;

extern sf::Texture playerTex;
extern std::unique_ptr<sf::Sprite> p_sprite;
extern std::unique_ptr<Player> p_player;

// load hitbox
extern std::vector<sf::FloatRect> hitBoxList;
extern bool hitboxDirty;
// Level Exit
extern sf::FloatRect exit_hitbox;
extern sf::Font font;
extern sf::Font title_font;
// Music
extern sf::Music music;
extern sf::SoundBuffer buffer;
extern std::unordered_map<SoundName,sf::SoundBuffer> soundBufferMap;
extern std::unordered_map<SoundName,std::shared_ptr<sf::Sound>> soundMap;

int initLevel();
int resetLevel();
int levelPass();
int init_audio();
int init_font();

#endif