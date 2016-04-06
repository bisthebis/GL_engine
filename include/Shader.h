#ifndef DEF_SHADER_HEADER
#define DEF_SHADER_HEADER

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <algorithm>

namespace GL
{
	class Shader
	{
		private:
			GLuint ID = 0;
			std::string vertexSource;
			std::string fragmentSource;

			GLuint compileShader(GLenum type, const std::string& file); //Gère la compilation d'un shader et lance les exceptions adéquates en cas d'erreur. Retourne ledit shader
		public:
			Shader(const std::string& vert, const std::string& frag);
			Shader(const Shader& src) = delete;
			Shader(Shader&& src);
			Shader& operator= (const Shader& src) = delete;
			Shader& operator= (Shader&& src);
			~Shader();

			GLuint getProgramID() const {return ID;}

			void charger(); //Doit appeler "compileShader" pour compiler les deux shaders, puis les linker et signaler les erreurs de Link.
				//Contrat : IN : deux strings valables comme chemins de fichier, OUT : ID représente un programme valide




	};

}

#endif
