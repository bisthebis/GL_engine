#version 450 core

in vec3 inColor;
out vec4 outColor;

layout (location = 0) uniform float ratio;

void main()
{
	outColor = ratio*vec4(inColor, 1.0);
}
