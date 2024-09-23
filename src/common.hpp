#pragma once
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <filesystem> 
#include <unordered_map>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dialog/boxer.h"
#include "fs/FileSystem.hpp"
#include "scene/RenderScene.hpp"
#include "audio/AudioManager.hpp"
#include "util/Util.hpp"
#include "shader/Shader.hpp"

class RenderScene;
class FileSystem;
class AudioManager;


namespace Common {
	extern GLFWwindow *MainWindow;
	extern float CurrentTime;
	extern RenderScene *CurrentScene;
	extern FileSystem *FS;
	extern AudioManager *Audio;

	extern bool wireframe;
	
	extern glm::vec2 screenResolution;
}