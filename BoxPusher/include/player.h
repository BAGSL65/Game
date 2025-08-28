#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "moveStateEnum.h"
#include "paras.h"

class Player {

public:
    MoveState moveState=MoveState::Idle;
    sf::Keyboard::Key lastKey;
    // float speed = 150.f;
    float step = 64.f;
    sf::Vector2i direction={0,0};
    sf::Sprite sprite;
    Player(sf::Sprite sprite) : sprite(sprite) {};
    void move(sf::Vector2i movement,const std::vector<sf::FloatRect>& hitboxList);
    sf::Vector2f getBoxAt();
    sf::Vector2i getDirection(){return direction;};
};
#endif