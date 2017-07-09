#version 330 core

in vec2 TexCoords;

uniform sampler2D screen_texture;

out vec4 texColor;

void main()
{
	texColor = vec4(vec3(texture(screen_texture, TexCoords)), 1.0f);
}