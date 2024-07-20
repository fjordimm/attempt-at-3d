
#version 150 core

uniform mat4 uni_model;
uniform mat4 uni_view;
uniform mat4 uni_proj;

in vec3 attrib_position;
in vec3 attrib_color;

out vec4 vCoord;
out vec3 vColor;

void main()
{
	vCoord = uni_model * vec4(attrib_position, 1.0);
	vColor = attrib_color;
	gl_Position = uni_proj * uni_view * uni_model * vec4(attrib_position, 1.0);
}
