#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <string.h>
#include "stateEnum.h"

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

void load_texture(std::unordered_map<TextureName,sf::Texture>& texture_map);
void load_sound_map(std::unordered_map<SoundName,sf::SoundBuffer>& soundBufferMap,std::unordered_map<SoundName,std::shared_ptr<sf::Sound>>& soundMap);
#endif