#include "../include/Shader.h"


Shader::~Shader()
{
	if(glIsProgram(ID))
	glDeleteProgram(ID);


}


