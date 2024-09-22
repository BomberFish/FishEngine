#pragma once
#include "../common.hpp"

class FileSystem {
public:
	std::string rootPath;
    FileSystem(std::string rootPath);
    ~FileSystem();

    std::string GetPath(const std::string &path);
    std::string GetShaderPath(const std::string &path);
    std::string GetTexturePath(const std::string &path);
    std::string GetModelPath(const std::string &path);
    std::string GetAudioPath(const std::string &path);
};
