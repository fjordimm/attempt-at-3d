
#version 150 core

uniform mat4 uni_SunRot;
uniform float uni_SunBrightness;
uniform float uni_SunAmbientLight;

in vec3 g_Normal;

out vec4 f_Color;

void main()
{

	vec4 rotatedNormal = uni_SunRot * vec4(normalize(g_Normal), 1.0);

	float shadingMult = uni_SunAmbientLight * rotatedNormal.z + (1.0 - uni_SunAmbientLight);

	vec3 baseColor = uni_SunBrightness * vec3(1.0, 1.0, 1.0);
	f_Color = vec4(shadingMult * baseColor, 1.0);
}
