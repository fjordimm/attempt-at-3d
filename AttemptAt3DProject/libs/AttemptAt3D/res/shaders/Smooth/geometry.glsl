
#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 v_Coord[];
in vec3 v_Normal[];

out vec3 g_Normal;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		g_Normal = v_Normal[i];
		EmitVertex();
	}

	EndPrimitive();
}
