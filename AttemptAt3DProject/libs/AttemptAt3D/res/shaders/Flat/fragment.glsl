
#version 150 core

uniform mat4 uni_SunRot;

in vec3 g_Normal;

out vec4 f_Color;

void main()
{

	vec4 rotatedNormal = uni_SunRot * vec4(g_Normal, 1.0);

	// float shadingMult = 0.5 * rotatedNormal.z + 0.5;
	float shadingMult = 0.35 * rotatedNormal.z + 0.65;

	f_Color = vec4(vec3(1.0, 1.0, 1.0) * shadingMult, 1.0);
}
