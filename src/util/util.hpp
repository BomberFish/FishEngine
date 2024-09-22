#pragma once
#include "../common.hpp"

namespace Util {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processShaderReturnValue(int success, unsigned int shader, const char* type);
}

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(std::string name);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};