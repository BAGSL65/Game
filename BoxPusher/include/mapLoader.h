#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// 最基本的自定义异常
class MapLoadException : public std::exception {
public:
    explicit MapLoadException(const std::string& message) 
        : msg_(message) {}
    
    const char* what() const noexcept override {
        return msg_.c_str();
    }
    
private:
    std::string msg_;
};

std::vector<std::vector<int>> loadFromCSV(const std::string& filename);
#endif