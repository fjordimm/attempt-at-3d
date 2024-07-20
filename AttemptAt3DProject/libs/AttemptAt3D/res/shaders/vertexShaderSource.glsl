
#version 150 core

uniform mat4 uni_transScale;
uniform mat4 uni_transRot;
uniform mat4 uni_transPos;
uniform mat4 uni_view;
uniform mat4 uni_proj;

in vec3 attrib_position;
in vec3 attrib_color;

out vec4 vCoord;
out vec3 vColor;

void main()
{
	vec4 trans = uni_transPos * uni_transRot * uni_transScale * vec4(attrib_position, 1.0);

	vCoord = trans;
	vColor = attrib_color;
	gl_Position = uni_proj * uni_view * trans;
}
