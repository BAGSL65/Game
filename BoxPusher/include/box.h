#ifndef BOX_H
#define BOX_H
#include <vector>
#include <SFML/Graphics.hpp>
class Box {
    public:
        bool sinked = false;
        float size = 64.0f;
        sf::FloatRect getFloatRect(){return sprite.getGlobalBounds();};
        sf::Vector2f position;
        sf::Sprite sprite;
        Box(sf::Sprite sprite,sf::Vector2f position,float size) : 
        sprite(sprite),position(position),size(size) {};


        void getPushed(sf::Vector2i direction,float BlockSize);
        
};
#endif