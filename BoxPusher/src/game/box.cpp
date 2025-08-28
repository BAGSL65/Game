#include "box.h"
bool Box::getPushed
    (
        sf::Vector2i direction,
        std::unordered_map<float,std::shared_ptr<Water>> water_map,
        const std::vector<sf::FloatRect>& hitboxList,
        sf::Vector2f& pushed_pos
    )
{
    // if box is sunk, do nothing
    if(sunk) return false;

    bool collision = false;
    sf::FloatRect hit_pos = sprite.getGlobalBounds();
    hit_pos.position.x+=direction.x*static_cast<int>(BlockSize);
    hit_pos.position.y+=direction.y*static_cast<int>(BlockSize);
    for (auto& hitbox : hitboxList) {
        if (hit_pos.findIntersection(hitbox)) {
            collision = true;
            break;
        }
    }
    sf::Vector2f next_pos = sprite.getPosition();
    next_pos.x+=direction.x*static_cast<int>(BlockSize);
    next_pos.y+=direction.y*static_cast<int>(BlockSize);
    if(water_map.find(vecToFloat(next_pos))!=water_map.end())
    {
        sunk = true;
        water_map[vecToFloat(next_pos)]->boxed = true;
        collision = false;
    }
    if(!collision){
        sprite.setPosition(next_pos);
        pushed_pos = next_pos;
        return true;
    }
    return false;
}

