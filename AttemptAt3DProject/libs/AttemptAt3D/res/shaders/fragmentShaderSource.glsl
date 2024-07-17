#version 150 core

in vec3 gColor;
in vec3 gNormal;

out vec4 outColor;

uniform mat4 sunRot;

void main()
{
	vec4 rotatedNormal = sunRot * vec4(gNormal, 1.0);

	// float shadingMult = 0.5 * rotatedNormal.z + 0.5;
	float shadingMult = 0.35 * rotatedNormal.z + 0.65;

	outColor = vec4(gColor * shadingMult, 1.0);
}