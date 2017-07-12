#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

//out vec3 ourColor;

out VS_OUT
{
	vec2 TexCoords;
	vec3 Normal;
	vec3 FragPos;
}vs_out;

uniform mat4 transform;
uniform mat4 model;

void main(void)
{
   vs_out.FragPos = vec3(model * vec4(position, 1.0));
   gl_Position = transform * model * vec4(position, 1.0f);
   vs_out.TexCoords = texCoords;
   vs_out.Normal = normal;
   //Normal = mat3(transpose(inverse(model))) * normal;
}
