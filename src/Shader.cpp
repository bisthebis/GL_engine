#include "../include/Shader.h"

#include <iostream>
#include <fstream>


Shader::Shader(const std::string& vert, const std::string& frag) : vertexSource(vert), fragmentSource(frag)
{

}

Shader::Shader(const Shader& src)  : vertexSource(src.vertexSource), fragmentSource(src.fragmentSource)
{
	charger();
}

Shader::Shader(Shader&& src)
{
	std::swap(vertexSource, src.vertexSource);
	std::swap(fragmentSource, src.fragmentSource);
	ID = src.ID;
	src.ID = 0; /*afin d'éviter que le programme ne soit détruit */
}

Shader& Shader::operator= (const Shader& src)
{
	vertexSource = src.vertexSource;
	fragmentSource = src.fragmentSource;
	charger();
	return *this;
}

Shader& Shader::operator= (Shader&& src)
{
	std::swap(vertexSource, src.vertexSource);
	std::swap(fragmentSource, src.fragmentSource);
	ID = src.ID;
	src.ID = 0;

	return *this; /*afin d'éviter que le programme ne soit détruit */
}

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
	return shader;

}

void Shader::charger()
{
	GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);

	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
