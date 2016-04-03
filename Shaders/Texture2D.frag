#version 450 core

in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D myTexture;


void main()
{
	outColor = texture(myTexture, TexCoords);
}
