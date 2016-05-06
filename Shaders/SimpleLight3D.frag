#version 450 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 fragPos;

out vec4 outColor;

uniform sampler2D myTexture;


layout (location = 3) uniform vec3 LightPos;


void main()
{
	//outColor = mix(texture(myTexture, TexCoords), texture(myTexture2, TexCoords), factor);
	//outColor = Normals;
	vec3 LightToObject = normalize(LightPos - fragPos);
	vec3 n = normalize(Normals);
	outColor = max(dot(LightToObject, n), 0.2) * texture(myTexture, TexCoords);
}
