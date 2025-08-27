#include "mapLoader.h"
std::vector<std::vector<int>> loadFromCSV(const std::string& filename) {
    std::vector<std::vector<int>> map;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw MapLoadException("Failed to open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;
        
        while (std::getline(ss, cell, ',')) {
            try {
                row.push_back(std::stoi(cell));
            } catch (...) {
                row.push_back(0); // 解析失败时使用默认值
            }
        }
        
        if (!row.empty()) {
            map.push_back(row);
        }
    }
    return map;
}