#include "box.h"

void Box::getPushed(sf::Vector2i direction,float BlockSize)
{
    sprite.move({sprite.getPosition().x+direction.x*BlockSize,
    sprite.getPosition().y+direction.y*BlockSize,});
}

