#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <string.h>
#include "textureName.h"

// 最基本的自定义异常
class LoadException : public std::exception {
public:
    explicit LoadException(const std::string& message) 
        : msg_(message) {}
    
    const char* what() const noexcept override {
        return msg_.c_str();
    }
    
private:
    std::string msg_;
};

int load_texture(std::unordered_map<TextureName,sf::Texture>& texture_map);
#endif