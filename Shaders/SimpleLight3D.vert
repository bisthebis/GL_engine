#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 UVs;
layout (location = 2) in vec3 normals;

out vec2 TexCoords;
out vec3 Normals;
out vec3 fragPos;


layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

void main()
{
	vec4 Pos = projection * view * model * vec4(pos, 1.0);
	gl_Position = Pos;
	TexCoords = UVs;
	Normals = (model * vec4(normals, 0.0)).xyz;
	fragPos = (model * vec4(pos, 1.0)).xyz;
}
