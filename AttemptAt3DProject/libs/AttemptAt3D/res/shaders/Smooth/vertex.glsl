
#version 150 core

uniform mat4 uni_transScale;
uniform mat4 uni_transRot;
uniform mat4 uni_transPos;
uniform mat4 uni_view;
uniform mat4 uni_proj;

in vec3 attrib_position;
in vec3 attrib_normal;

out vec4 vCoord;
out vec3 vNormal;

void main()
{
	vec4 trans = uni_transPos * uni_transRot * uni_transScale * vec4(attrib_position, 1.0);

	vCoord = trans;
	vNormal = attrib_normal;
	gl_Position = uni_proj * uni_view * trans;
}
