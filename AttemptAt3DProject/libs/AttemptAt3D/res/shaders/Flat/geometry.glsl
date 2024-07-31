
#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 v_Coord[];

out vec3 g_Normal;

void main()
{
	vec3 normalVector = normalize(cross((v_Coord[1] - v_Coord[0]).xyz, (v_Coord[2] - v_Coord[0]).xyz));

	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		g_Normal = normalVector;
		EmitVertex();
	}

	EndPrimitive();
}
