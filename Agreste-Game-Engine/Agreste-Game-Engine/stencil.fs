#version 430 core

in vec4 stencilColor;

out vec4 FragColor;

void main()
{
    FragColor = stencilColor;
}