#version 450 core

in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D myTexture;
uniform sampler2D myTexture2;

layout (location = 3) uniform float factor;


void main()
{
	outColor = mix(texture(myTexture, TexCoords), texture(myTexture2, TexCoords), factor);
}
