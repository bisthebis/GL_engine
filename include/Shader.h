#ifndef DEF_SHADER_HEADER
#define DEF_SHADER_HEADER

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <string>

class Shader
{
	private:
		GLuint ID = 0;
		std::string vertexSource;
		std::string fragmentSource;		
	public: 
		Shader(const std::string& vert, const std::string& frag) : vertexSource(vert), fragmentSource(frag) {}
		~Shader();
	



};

#endif
