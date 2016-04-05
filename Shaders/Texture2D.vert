#version 450 core

in vec2 pos;
in vec2 UVs;

out vec2 TexCoords;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(pos, 1.0, 1.0);
	gl_Position.z = clamp(gl_Position.z, -0.9, 0.9);
	TexCoords = UVs;
}
