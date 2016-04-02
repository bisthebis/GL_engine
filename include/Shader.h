#ifndef DEF_SHADER_HEADER
#define DEF_SHADER_HEADER

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <algorithm>

class Shader
{
	private:
		GLuint ID = 0;
		std::string vertexSource;
		std::string fragmentSource;		
		
		void compileShader(GLuint& shader, GLenum type, const std::string& file); //Gère la compilation d'un shader et lance les exceptions adéquates en cas d'erreur
	public: 
		Shader(const std::string& vert, const std::string& frag) : vertexSource(vert), fragmentSource(frag) {} //Construire depuis deux fichiers
		Shader(const Shader& src) : vertexSource(src.vertexSource), fragmentSource(src.fragmentSource) {charger();} //constructeur de copie
		Shader(Shader&& src){std::swap(vertexSource, src.vertexSource); std::swap(fragmentSource, src.fragmentSource); ID = src.ID; src.ID = 0; /*afin d'éviter que le programme ne soit détruit */} //Constructeur de déplacement
		Shader& operator= (const Shader& src) {vertexSource = src.vertexSource; fragmentSource = src.fragmentSource; charger();} //Assignement de copie
		Shader& operator= (Shader&&) {std::swap(vertexSource, src.vertexSource); std::swap(fragmentSource, src.fragmentSource); ID = src.ID; src.ID = 0; /*afin d'éviter que le programme ne soit détruit */} //Assignement de déplacement
		~Shader(); //Destructeur
		
		GLuint getProgramID() const {return ID;}
		
		void charger(); //Doit appeler "compileShader" pour compiler les deux shaders, puis les linker et signaler les erreurs de Link. 
			//Contrat : IN : deux strings valables comme chemins de fichier, OUT : ID représente un programme valide
	



};

#endif
