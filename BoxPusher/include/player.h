#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Player {

public:
    sf::Vector2f velocity;
    float speed = 150.f;
    sf::Sprite sprite;
    Player(const sf::Texture& texture) : sprite(texture) {};
    void update(float deltaTime, const std::vector<sf::FloatRect>& walls);
};
#endif