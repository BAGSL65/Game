#include "player.h"

void Player::move(sf::Vector2i movement,const std::vector<sf::FloatRect>& walls) {

    if(moveState == MoveState::Idle){
        // 跨步移动
        sf::FloatRect nextPos = sprite.getGlobalBounds();
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

        

        nextPos.position.x += horizontal_movement;
        nextPos.position.y += vertical_movement;

        bool collision = false;
        for (auto& wall : walls) {
            if (nextPos.findIntersection(wall)) {
                collision = true;
                break;
            }
        }
        if (!collision) {
            sprite.move({horizontal_movement,vertical_movement});
        }
    }
}

sf::Vector2f Player::getBoxAt(float BlockSize)
{
    return {position.x + direction.x * BlockSize, position.y + direction.y * BlockSize};
}
