
#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 vCoord[];

out vec3 gNormal;

void main()
{
	vec3 normalVector = normalize(cross((vCoord[1] - vCoord[0]).xyz, (vCoord[2] - vCoord[0]).xyz));

	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gNormal = normalVector;
		EmitVertex();
	}

	EndPrimitive();
}
