// GLSL Fragment Shader
#version 330 core
out vec4 fragColor;
in vec3 vertexColor;

void main()
{
    fragColor = vec4(vertexColor, 1.0f);
} 