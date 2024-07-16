#version 150 core

in vec3 position;
in vec3 color;

out vec3 vColor;
out vec4 vCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vColor = color;
	vCoord = model * vec4(position, 1.0);
	gl_Position = proj * view * model * vec4(position, 1.0);
}