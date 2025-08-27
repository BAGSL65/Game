#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "moveStateEnum.h"
#include <vector>

class Player {

public:
    MoveState moveState=MoveState::Idle;
    sf::Keyboard::Key lastKey;
    // float speed = 150.f;
    float step = 64.f;
    sf::Vector2i direction={0,0};
    sf::Vector2f position;
    sf::Sprite sprite;
    Player(sf::Sprite sprite,sf::Vector2f position) : sprite(sprite),position(position) {};
    void move(sf::Vector2i movement,const std::vector<sf::FloatRect>& walls);
    sf::Vector2f getBoxAt(float BlockSize);
    sf::Vector2i getDirection(){return direction;};
};
#endif