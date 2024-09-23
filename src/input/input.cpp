#include "Input.hpp"

using namespace Common;
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		case GLFW_KEY_F:
			Audio->playSound("fart.wav");
			break;
		case GLFW_KEY_T:
			CurrentScene = (new TriangleScene());
			break;
		case GLFW_KEY_G:
			CurrentScene = (new ContainerScene());
			break;
		case GLFW_KEY_R:
			CurrentScene = (new RotatingTriangleScene());
			break;
		case GLFW_KEY_E:
			CurrentScene = (new RotatingContainerScene());
			break;
		case GLFW_KEY_C:
			CurrentScene = (new CubeScene());
			break;
		case GLFW_KEY_W:
			if (wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wireframe = false;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireframe = true;
			}
		
		default:
			break;
		}
	}
}
