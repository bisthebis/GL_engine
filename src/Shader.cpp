#include "../include/Shader.h"

#include <iostream>
#include <fstream>

Shader::~Shader()
{
	if(glIsProgram(ID))
	glDeleteProgram(ID);


}

GLuint Shader::compileShader(GLenum type, const std::string& file)
{
	GLuint shader = glCreateShader(type);
	if(!shader)
		std::cerr << "Type de shader incompatible ! " << std::endl;
	
	std::ifstream fichier;
	fichier.open(file);
	
	if(!fichier)
		std::cerr << "Fichier introuvable ! " << file << std::endl;
	
	std::string ligne;
	std::string Source;
	

	while(std::getline(fichier, ligne))
        Source += ligne + '\n';
	
	fichier.close();
	
	const GLchar* code = Source.c_str();
	
	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);
	
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

	if(erreurCompilation != GL_TRUE)
	{


	GLint tailleErreur(0);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

	std::string erreur;			
	erreur.resize(tailleErreur+1);



	glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, &erreur[0]);
        erreur[tailleErreur] = '\0';

	std::cerr << erreur << std::endl;
	glDeleteShader(shader);

        ///THROW EXCEPTION
	}
	
	
}

void Shader::charger()
{
	
	
}
