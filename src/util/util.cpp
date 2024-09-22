#include "util.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	printf("window resized to %dx%d\n", width, height);
    glViewport(0, 0, width, height);
}  