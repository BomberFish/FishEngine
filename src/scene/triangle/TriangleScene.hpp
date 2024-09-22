#pragma once

#include "../RenderScene.hpp"

const char *vertexShaderSource = R"(
// GLSL Vertex Shader
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 vertexColor;
void main()
{
    // gl_Position is a built-int GLSL output variable. The value
    // we store here will be used by OpenGL to position the vertex.
    gl_Position = vec4(position, 1.0);

    // Just copy the vertex attribute color to our output variable
    // vertexColor, so it's "propagated" down the pipeline until reaching
    // the fragment shader.
    vertexColor = color;
} 
)";
const char *fragmentShaderSource = R"(
// GLSL Fragment Shader
#version 330 core
out vec4 fragColor;
in vec3 vertexColor;

void main()
{
    fragColor = vec4(vertexColor, 1.0f);
} 
)";

void processShaderReturnValue(int success, unsigned int shader, const char* type) {
	if(!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		dialog::show(infoLog, type);
	}
}

class TriangleScene : public RenderScene {
public:
    TriangleScene() {
        name = "triangle";
    }

    void render() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		float vertices[] = {
			// For visualization: each row is a vertex.
			// Each vertex has position [x, y, z] and color [r, g, b]
			-0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,   // red color for this vertex
			0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,   // green color
			0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0    // blue color for our top vertex
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);  

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Unbind VAO after setting vertex attributes

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int  success;;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		processShaderReturnValue(success, vertexShader, "Vertex Shader Compilation Failed!");

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		processShaderReturnValue(success, fragmentShader, "Fragment Shader Compilation Failed!");

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		processShaderReturnValue(success, shaderProgram, "Shader Program Linking Failed!");

		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Clean up
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
    }
};