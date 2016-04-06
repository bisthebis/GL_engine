#version 450 core

in vec3 pos;
in vec2 UVs;

out vec2 TexCoords;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	TexCoords = UVs;
}
