#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> loadFromCSV(const std::string& filename);
#endif