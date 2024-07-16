#version 150 core

in vec3 gColor;
in vec3 gNormal;

out vec4 outColor;

void main()
{
	float shadingMult = 0.5f * gNormal.z + 0.5f;

	outColor = vec4(gColor * shadingMult, 1.0);
}