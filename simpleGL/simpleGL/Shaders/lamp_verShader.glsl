#version 330 core

layout (location = 0) in vec3 position;


uniform mat4 transform;
uniform mat4 model;

void main(void)
{
   gl_Position = transform * model * vec4(position, 1.0);
}