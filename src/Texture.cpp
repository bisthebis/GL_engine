#include <string>
#include <SFML/Graphics.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include "Texture.h"
#include "easylogging++.h"


namespace glUtils
{
	Texture::~Texture()
	{
		if(glIsTexture(TextureID))
		{
			glDeleteTextures(1, &TextureID);
			LOG(INFO) << "Deleting Texture";
		}

	}

	void Texture::loadFromFile(const std::string& src)
	{

			sf::Image img;
			img.loadFromFile(src);
			img.flipVertically();

			glGenTextures(1, &TextureID);
			glBindTexture(GL_TEXTURE_2D, TextureID);

			// Set our texture parameters
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    // Set texture filtering
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			unsigned int width = img.getSize().x;
			unsigned int height = img.getSize().y;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

			LOG(INFO) << "Successfully loaded texture from : " << src;

	}

	GLuint Texture::getProgramID(){return TextureID;}

}
