
#version 150 core

uniform mat4 uni_TransScale;
uniform mat4 uni_TransRot;
uniform mat4 uni_TransPos;
uniform mat4 uni_View;
uniform mat4 uni_Proj;

in vec3 attrib_Position;

out vec4 v_Coord;

void main()
{
	vec4 trans = uni_TransPos * uni_TransRot * uni_TransScale * vec4(attrib_Position, 1.0);

	v_Coord = trans;
	gl_Position = uni_Proj * uni_View * trans;
}
