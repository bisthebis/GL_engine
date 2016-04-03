#version 450 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

layout (location = 0) uniform vec2 translation;

out vec3 inColor;

void main()
{
	gl_Position = vec4(pos+translation, 0.0, 1.0);
	inColor = col;
}
