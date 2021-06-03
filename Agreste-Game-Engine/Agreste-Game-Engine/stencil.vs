#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 stencilColor;

uniform vec4 stencil;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    stencilColor = stencil;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}