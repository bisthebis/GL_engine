#version 450 core

in vec2 pos;
in vec2 UVs;

out vec2 TexCoords;

layout (location = 0) uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(pos, 0.0, 1.0);
	TexCoords = UVs;
}
