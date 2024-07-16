#version 150 core

in vec3 Color;
in float Bruh;

out vec4 outColor;

void main()
{
	if (Bruh > 0.3)
	{
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		outColor = vec4(Color, 1.0);
	}
}