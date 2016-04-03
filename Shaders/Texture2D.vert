#version 450 core

in vec2 pos;
in vec2 UVs;

out vec2 TexCoords;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	TexCoords = UVs;
}
