#pragma once
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <filesystem> 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "dialog/boxer.h"
#include "fs/FileSystem.hpp"
#include "scene/RenderScene.hpp"
#include "util/util.hpp"

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

namespace Common {
	extern GLFWwindow *MainWindow;
	extern float CurrentTime;
	extern RenderScene *CurrentScene;
	extern FileSystem *FS;
}