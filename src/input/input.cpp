#include "input.hpp"

using namespace Common;

void processInput(void)
{
    if(glfwGetKey(MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(MainWindow, true);
}