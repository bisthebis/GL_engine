#include "../include/Shader.h"


Shader::~Shader()
{
	if(glIsProgram(ID))
	glDeleteProgram(ID);


}

void Shader::compileShader(GLuint& shader, GLenum type, const std::string& file)
{
	
	
}

void Shader::charger()
{
	
	
}