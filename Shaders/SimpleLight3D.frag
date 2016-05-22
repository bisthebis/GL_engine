#version 450 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 fragPos;

out vec4 outColor;

uniform sampler2D DiffuseText;
uniform sampler2D SpecularText;


layout (location = 3) uniform vec3 LightPos;


void main()
{
	//outColor = mix(texture(DiffuseText, TexCoords), texture(SpecularText, TexCoords), factor);
	//outColor = Normals;
	vec3 LightToObject = normalize(LightPos - fragPos);
	const float LightReduction = 15.0 / length(LightPos - fragPos);
	vec3 n = normalize(Normals);
	outColor = LightReduction * max(dot(LightToObject, n), 0.2) * texture(DiffuseText, TexCoords);
}
