#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #define MKDIR(path) mkdir(path, 0755)
#endif
class Logger {
public:
    std::ofstream file;
    Logger(const char* path) {
        // 提取目录路径并创建
        std::string dirPath = extractDirectoryPath(path);
        if (!dirPath.empty()) {
            createDirectoriesRecursive(dirPath);
        }
        file.open(path,std::ios::out);
    }
    ~Logger() {
        file.close();
    }
    void log(std::string message) {
        file << message << std::endl;
    }

private:
    // 提取文件路径中的目录部分
    std::string extractDirectoryPath(const std::string& filePath) {
        size_t pos = filePath.find_last_of("/\\");
        if (pos != std::string::npos) {
            return filePath.substr(0, pos);
        }
        return ""; // 没有目录部分
    }    
    bool directoryExists(const std::string& path) {
        struct stat info;
        return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
    }

    bool createDirectory(const std::string& path) {
        return MKDIR(path.c_str()) == 0;
    }

    bool createDirectoriesRecursive(const std::string& path) {
        // 如果目录已存在，直接返回true
        if (directoryExists(path)) {
            return true;
        }
        
        // 找到最后一个路径分隔符
        size_t pos = path.find_last_of("/\\");
        if (pos != std::string::npos) {
            // 递归创建父目录
            std::string parentPath = path.substr(0, pos);
            if (!createDirectoriesRecursive(parentPath)) {
                return false;
            }
        }
        // 创建当前目录
        return createDirectory(path);
    }
};
#endif