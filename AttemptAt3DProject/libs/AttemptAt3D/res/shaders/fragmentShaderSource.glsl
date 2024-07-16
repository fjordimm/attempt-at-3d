#version 150 core

in vec3 gColor;
in vec3 gNormal;

out vec4 outColor;

void main()
{
	float theta = radians(-90.0);
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	mat3 rotationMatrix;
	rotationMatrix[0] = vec3(cosTheta, 0, sinTheta);
	rotationMatrix[1] = vec3(0, 1, 0);
	rotationMatrix[2] = vec3(-sinTheta, 0, cosTheta);

	vec3 rotatedNormal = rotationMatrix * gNormal;

	float shadingMult = 0.35 * rotatedNormal.z + 0.65;

	outColor = vec4(gColor * shadingMult, 1.0);
}