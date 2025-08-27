#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>

class Logger {
public:
    std::ofstream file;
    Logger(const char* path) {
        file.open(path,std::ios::out);
    }
    ~Logger() {
        file.close();
    }
    void log(std::string message) {
        file << message << std::endl;
    }
};
#endif