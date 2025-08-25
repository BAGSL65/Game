#include "player.h"

void Player::update(float deltaTime, const std::vector<sf::FloatRect>& walls) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1;


    sf::FloatRect nextPos = sprite.getGlobalBounds();
    if (movement.x != 0 && movement.y != 0){
        movement.x /= sqrt(2.f);
        movement.y /= sqrt(2.f);
    }
    nextPos.position.x += movement.x * speed * deltaTime;
    nextPos.position.y += movement.y * speed * deltaTime;

    bool collision = false;
    for (auto& wall : walls) {
        if (nextPos.findIntersection(wall)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        sprite.move(movement * speed * deltaTime);
    }
}