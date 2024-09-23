#include "Util.hpp"
#include "../common.hpp"

namespace Util {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		printf("window resized to %dx%d\n", width, height);
		Common::screenResolution = glm::vec2(width, height);
		glViewport(0, 0, width, height);
	}  
}