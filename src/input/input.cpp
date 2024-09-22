#include "input.hpp"

using namespace Common;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		Audio->playSound("fart.wav");
}
