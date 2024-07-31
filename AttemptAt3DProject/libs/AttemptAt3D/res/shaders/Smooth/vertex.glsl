
#version 150 core

uniform mat4 uni_TransScale;
uniform mat4 uni_TransRot;
uniform mat4 uni_TransPos;
uniform mat4 uni_View;
uniform mat4 uni_Proj;

in vec3 attrib_Position;
in vec3 attrib_Normal;

out vec4 v_Coord;
out vec3 v_Normal;

void main()
{
	vec4 trans = uni_TransPos * uni_TransRot * uni_TransScale * vec4(attrib_Position, 1.0);

	v_Coord = trans;
	v_Normal = attrib_Normal;
	gl_Position = uni_Proj * uni_View * trans;
}
