// GLSL Vertex Shader
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // gl_Position is a built-int GLSL output variable. The value
    // we store here will be used by OpenGL to position the vertex.
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // Just copy the vertex attribute color to our output variable
    // vertexColor, so it's "propagated" down the pipeline until reaching
    // the fragment shader.
    vertexColor = color;
} 