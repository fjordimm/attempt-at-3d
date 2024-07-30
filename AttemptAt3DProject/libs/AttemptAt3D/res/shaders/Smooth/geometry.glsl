
#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 vCoord[];
in vec3 vNormal[];

out vec3 gNormal;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gNormal = vNormal[i];
		EmitVertex();
	}

	EndPrimitive();
}
