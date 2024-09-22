#include "Input.hpp"

using namespace Common;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		Audio->playSound("fart.wav");
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		Common::CurrentScene = new TriangleScene();
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		Common::CurrentScene = new ContainerScene();
}
