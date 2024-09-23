#pragma once
#include "../fs/FileSystem.hpp"
#include "../common.hpp"

namespace Util {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processShaderReturnValue(int success, unsigned int shader, const char* type);
}