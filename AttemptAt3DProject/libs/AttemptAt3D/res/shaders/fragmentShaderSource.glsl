
#version 150 core

uniform mat4 uni_sunRot;

in vec3 gColor;
in vec3 gNormal;

out vec4 outColor;

void main()
{
	vec4 rotatedNormal = uni_sunRot * vec4(gNormal, 1.0);

	// float shadingMult = 0.5 * rotatedNormal.z + 0.5;
	float shadingMult = 0.35 * rotatedNormal.z + 0.65;

	outColor = vec4(gColor * shadingMult, 1.0);
}
