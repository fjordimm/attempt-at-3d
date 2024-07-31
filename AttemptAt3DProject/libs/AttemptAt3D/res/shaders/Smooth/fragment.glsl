
#version 150 core

uniform mat4 uni_sunRot;

in vec3 gNormal;

out vec4 outColor;

const highp float DITHERING_NOISE_GRANULARITY = 0.5 / 255.0;
highp float dithering_random(highp vec2 coords)
{
	return fract(sin(dot(coords.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	vec4 rotatedNormal = uni_sunRot * vec4(gNormal, 1.0);

	// float shadingMult = 0.5 * rotatedNormal.z + 0.5;
	float shadingMult = 0.35 * rotatedNormal.z + 0.65;
	shadingMult += mix(-DITHERING_NOISE_GRANULARITY, DITHERING_NOISE_GRANULARITY, dithering_random(rotatedNormal.xy));

	outColor = vec4(vec3(1.0, 1.0, 1.0) * shadingMult, 1.0);
}
