#include "player.h"
void Player::move(sf::Vector2i movement,const std::vector<sf::FloatRect>& hitboxList) {

    if(moveState == MoveState::Idle){
        // 跨步移动
        sf::FloatRect hit_pos = sprite.getGlobalBounds();
        float vertical_movement = 0;
        float horizontal_movement = 0;

        if (movement.x > 0) {
            horizontal_movement = step;
            direction = {1,0};
        } 
        else if (movement.x < 0) {
            horizontal_movement = -step;
            direction = {-1,0};
        }
        else
        {
            if (movement.y > 0) {
                vertical_movement = -step;
                direction = {0,-1};
            } 
            else if (movement.y < 0) {
                vertical_movement = step;
                direction = {0,1};
            }
        }

        

        hit_pos.position.x += horizontal_movement;
        hit_pos.position.y += vertical_movement;

        bool collision = false;
        for (auto& hitbox : hitboxList) {
            if (hit_pos.findIntersection(hitbox)) {
                collision = true;
                break;
            }
        }
        if (!collision) {
            sf::Vector2f next_pos = sprite.getPosition();
            next_pos.x += horizontal_movement;
            next_pos.y += vertical_movement;
            sprite.setPosition(next_pos);
        }
    }
}

sf::Vector2f Player::getBoxAt()
{
    sf::Vector2f position = sprite.getPosition();
    return {position.x + direction.x * static_cast<int>(BlockSize),position.y + direction.y * static_cast<int>(BlockSize)};
}
