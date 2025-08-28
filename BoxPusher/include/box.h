#ifndef BOX_H
#define BOX_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "water.h"
#include "common_tool.h"
class Box {
    public:
        bool sunk = false;
        float size = 64.0f;
        sf::FloatRect getFloatRect(){return sprite.getGlobalBounds();};
        sf::Sprite sprite;
        Box(sf::Sprite sprite,float size) : 
        sprite(sprite),size(size) {};


        bool getPushed
        (
            sf::Vector2i direction,
            std::unordered_map<float,std::shared_ptr<Water>> water_map,
            const std::vector<sf::FloatRect>& hitboxList,
            sf::Vector2f& pushed_pos
        );
        
};
#endif