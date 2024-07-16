#version 150 core

in vec3 position;
in vec3 color;

out vec3 Color;
out float Bruh;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	Color = color;
	Bruh = position.z;
	gl_Position = proj * view * model * vec4(position, 1.0);
}