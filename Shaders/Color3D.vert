#version 450 core

in vec3 pos;
in vec3 Col;

out vec3 inColor;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(pos, 1.0);
	inColor = Col;
}
