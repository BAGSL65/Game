#include "common_tool.h"
float vecToFloat(sf::Vector2f vec)
{
    return (int)vec.x/BlockSize*BlockSize + (int)vec.y/BlockSize*MapLength*BlockSize;
}
sf::Vector2f conv2iTo2f(sf::Vector2i vec){
    return sf::Vector2f((float)vec.x,(float)vec.y);
}

sf::Vector2f conv2uTo2f(sf::Vector2u vec){
    return sf::Vector2f((float)vec.x,(float)vec.y);
}