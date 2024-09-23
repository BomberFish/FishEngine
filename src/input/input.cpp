#include "Input.hpp"

using namespace Common;
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		Audio->playSound("fart.wav");
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		CurrentScene = new TriangleScene();
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		CurrentScene = new ContainerScene();
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		CurrentScene = new RotatingTriangleScene();
}
