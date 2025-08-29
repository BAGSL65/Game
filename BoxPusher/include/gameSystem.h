#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include "gameState.h"
#include "box.h"
#include "player.h"
#include "water.h"
#include "mapLoader.h"
#include "textureNameEnum.h"
#include "textureLoader.h"
#include "common_tool.h"
#include "logger.h"

extern Logger logger;
extern GameState gameState;

extern std::vector<std::vector<sf::Sprite>> sBlockList2d;
extern std::vector<sf::FloatRect> sBlockBoundsList;
// 使用智能指针（更安全）
extern std::vector<std::shared_ptr<Water>> waterList;
extern std::vector<std::shared_ptr<Box>> boxList;
extern std::unordered_map<float, std::shared_ptr<Water>> waterMap;
extern std::unordered_map<float, std::shared_ptr<Box>> boxMap;

extern std::vector<std::vector<int>> mapData;
extern std::unordered_map<TextureName, sf::Texture> texture_map;

extern sf::Texture playerTex;
extern std::unique_ptr<sf::Sprite> p_sprite;
extern std::unique_ptr<Player> p_player;

//load hitbox
extern std::vector<sf::FloatRect> hitBoxList;
extern bool hitboxDirty;
//Level Exit
extern sf::FloatRect exit_hitbox;
extern sf::Font font;
int initLevel();
int resetLevel();
int levelPass();

#endif