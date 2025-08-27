#ifndef WATER_H
#define WATER_H
#include <vector>
#include <SFML/Graphics.hpp>
class Water {
    public:
        
        bool boxed = false;
        float size=64.0f;
        
        sf::Vector2f position;
        sf::Sprite sprite;
        Water(sf::Sprite sprite,sf::Vector2f position,float size) : 
        sprite(sprite),position(position),size(size) {};
        sf::FloatRect getFloatRect(){return sprite.getGlobalBounds();};
};
#endif