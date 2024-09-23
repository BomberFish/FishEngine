#include "common.hpp"
#include "util/Util.hpp"
#include "input/Input.hpp"

#include "scene/Scenes.hpp"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


namespace Common
{
	GLFWwindow *MainWindow;
	float CurrentTime;
	RenderScene *CurrentScene;
	FileSystem *FS;
	AudioManager *Audio;

	glm::vec2 screenResolution = glm::vec2(WIN_WIDTH, WIN_HEIGHT);

	bool wireframe = false;

}

using namespace Common;
using namespace Util;

int main(int argc, char** argv) {
	printf("Hello World!\n");

	std::string dataDir = "data";

	if (argc > 1) {
		printf("Called with arguments:\n");
		for (int i = 0; i < argc; i++) {
			printf("  %d: %s\n", i, argv[i]);
		}

		dataDir = argv[1];
	}

	try {
		FS = new FileSystem(dataDir);
	} catch (std::exception &e) {
		std::string msg = "Could not initialize file system: ";
		msg += e.what();
		fprintf(stderr, "%s\n", msg.c_str());
		dialog::show(msg.c_str(), "Critical Error");
		return -1;
	}

	try {
		Audio = new AudioManager();
	} catch (std::exception &e) {
		std::string msg = "Could not initialize audio manager: ";
		msg += e.what();
		fprintf(stderr, "%s\n", msg.c_str());
		dialog::show(msg.c_str(), "Critical Error");
		return -1;
	}
	
	Audio->playSound("gamecube.wav");

    /* Initialize the library */
    if (!glfwInit()) {
		fprintf(stderr, "Could not initialize GLFW!\n");
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
		fprintf(stderr, "Failed to create a window!\n");
		dialog::show("Failed to create a window!", "GLFW Error");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(MainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Could not initialize GLAD!\n");
		dialog::show("Could not initialize GLAD!", "Critical Error");
		return -1;
	}   
	
	glEnable(GL_DEPTH_TEST);

	printf("OpenGL %s\n", glGetString(GL_VERSION));

	glfwSetKeyCallback(MainWindow, key_callback);
	glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);  
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	TriangleScene triangle;
	CurrentScene = &triangle;

	double previousTime = glfwGetTime();
	int frameCount = 0;


	glClearColor(0.066f, 0.066f, 0.1f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(MainWindow)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CurrentTime = glfwGetTime();

		double delta = CurrentTime - previousTime;
		frameCount++;
		// If a second has passed. 	
		if ( delta >= 1.0 )
		{
			double fps = double(frameCount) / delta;
			std::stringstream ss;
         	ss << "FishEngine" << " [" << fps << " FPS]";
			// Display the frame count here any way you want.
			glfwSetWindowTitle(MainWindow, ss.str().c_str());

			frameCount = 0;
			previousTime = CurrentTime;
		}

		if (CurrentScene != nullptr) {
			CurrentScene->render();
		}

        /* Swap front and back buffers */
        glfwSwapBuffers(MainWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
	printf("Goodbye!\n");
	delete Audio;
    glfwTerminate();
    return 0;
}