#include "util.hpp"

namespace Util {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		printf("window resized to %dx%d\n", width, height);
		glViewport(0, 0, width, height);
	}  

	void processShaderReturnValue(int success, unsigned int shader, const char* type) {
		if(!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			dialog::show(infoLog, type);
			fprintf(stderr, "%s\n", infoLog);
		}
	}
}


Shader::Shader(std::string name) {
	printf("Loading shader: %s\n", name.c_str());
	std::string vertexPathStr = Common::FS->GetShaderPath(name + ".vsh");
	std::string fragmentPathStr = Common::FS->GetShaderPath(name + ".fsh");
	const char* vertexPath = vertexPathStr.c_str();
	const char* fragmentPath = fragmentPathStr.c_str();
	
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
		std::string msg = "Could not read from shader file: ";
		msg += vertexPath;
		msg += " or ";
		msg += fragmentPath;
		msg += ": ";
		msg += e.what();
        dialog::show(msg.c_str(), "Shader Error");
		fprintf(stderr, "%s\n", msg.c_str());
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	Util::processShaderReturnValue(success, vertex, "Vertex Shader Compilation Failed!");
	
	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	Util::processShaderReturnValue(success, fragment, "Fragment Shader Compilation Failed!");

	
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	Util::processShaderReturnValue(success, ID, "Shader Program Linking Failed!");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}


void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}