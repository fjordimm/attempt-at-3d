#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vColor[];

out vec3 fColor;

void main()
{
	// gl_Position = gl_in[0].gl_Position;
	// EmitVertex();

	// gl_Position = gl_in[1].gl_Position;
	// EmitVertex();

	// gl_Position = gl_in[2].gl_Position;
	// EmitVertex();

	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		fColor = vColor[i];
		EmitVertex();
	}

	EndPrimitive();
}