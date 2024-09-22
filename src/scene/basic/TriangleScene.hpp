#pragma once

#include "../RenderScene.hpp"

using namespace Util;

class TriangleScene : public RenderScene {
public:
	TriangleScene() : shader("triangle") {
		name = "triangle";


		float vertices[] = {
			// For visualization: each row is a vertex.
			// Each vertex has position [x, y, z] and color [r, g, b]
			-0.5f, -0.5f, 0.0f,     1.0, 0.0, 0.0,   // red color for this vertex
			0.5f, -0.5f, 0.0f,      0.0, 1.0, 0.0,   // green color
			0.0f,  0.5f, 0.0f,      0.0, 0.0, 1.0    // blue color for our top vertex
		};

		glGenBuffers(1, &VBO);

		glGenVertexArrays(1, &VAO);  

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0); // Unbind VAO after setting vertex attributes
	}

	~TriangleScene() {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

    void render() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		this->shader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    }
private:
	Shader shader;
	unsigned int VBO;
	unsigned int VAO;
};