#version 150 core

in vec3 gColor;
in vec3 gNormal;

out vec4 outColor;

void main()
{
	// float theta = radians(-90.0);
	// float cosTheta = cos(theta);
	// float sinTheta = sin(theta);
	float alpha = radians(0.0);
	float beta = radians(0.0);
	float gamma = radians(90.0);
	float cA = cos(alpha);
	float sA = sin(alpha);
	float cB = cos(beta);
	float sB = sin(beta);
	float cG = cos(gamma);
	float sG = sin(gamma);
	mat3 rotationMatrix;
	rotationMatrix[0] = vec3(cA*cB, cA*sB*sG-sA*cG, cA*sB*cG+sA*sG);
	rotationMatrix[1] = vec3(sA*cB, sA*sB*sG+cA*cG, sA*sB*cG-cA*sG);
	rotationMatrix[2] = vec3(-sG, cB*sG, cB*cG);

	vec3 rotatedNormal = rotationMatrix * gNormal;

	float shadingMult = 0.35 * rotatedNormal.z + 0.65;

	outColor = vec4(gColor * shadingMult, 1.0);
}