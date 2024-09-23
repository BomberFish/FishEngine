#pragma once

#include "../RenderScene.hpp"

using namespace Util;

class RotatingTriangleScene : public RenderScene {
public:
	RotatingTriangleScene() : shader("triangle_rot") {
		name = "rot_triangle";


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

	~RotatingTriangleScene() {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

    void render() override {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.5f, 0.5f, 1.0f));

		this->shader.use();
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    }
private:
	Shader shader;
	unsigned int VBO;
	unsigned int VAO;
};