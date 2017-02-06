#version 330 core

in vec3 pos;
in vec2 UVs;
in vec3 normals;

out vec2 TexCoords;
out vec3 Normals;
out vec3 fragPos;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vec4 Pos = projection * view * model * vec4(pos, 1.0);
	gl_Position = Pos;
	TexCoords = UVs;
	Normals = (model * vec4(normals, 0.0)).xyz;
	fragPos = (model * vec4(pos, 1.0)).xyz;
}
