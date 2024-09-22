#include "common.hpp"
#include "util/util.hpp"
#include "input/input.hpp"
#include "scene/triangle/TriangleScene.hpp"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

namespace Common
{
	GLFWwindow *MainWindow;
}

using namespace Common;

int main(int argc, char** argv) {
	printf("Hello World!\n");

    /* Initialize the library */
    if (!glfwInit()) {
		printf("Could not initialize GLFW!\n");
		dialog::show("Could not initialize GLFW!", "Critical Error");
        return -1;
	}

	// Add hints to make it use a modern version of OGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    MainWindow = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Main Window", NULL, NULL);
	
    if (!MainWindow) {
		printf("Failed to create a window!\n");
		dialog::show("Failed to create a window!", "GLFW Error");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(MainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Could not initialize GLAD!\n");
		dialog::show("Could not initialize GLAD!", "Critical Error");
		return -1;
	}   
	

	printf("OpenGL %s\n", glGetString(GL_VERSION));


	glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);  
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	TriangleScene triangle;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(MainWindow)) {
		processInput();
        /* Render here */
		glClearColor(0.066f, 0.066f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		triangle.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(MainWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
	printf("Goodbye!\n");
    glfwTerminate();
    return 0;
}