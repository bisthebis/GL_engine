#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Shader.h"
#include "../include/MyException.h"
#include "../include/Texture.h"

#include "../include/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;


	sf::Window window(sf::VideoMode(200, 200), "OpenGL works!", sf::Style::Default, settings);
	glewInit();

	GL::Shader shader("Shaders/Texture2D.vert", "Shaders/Texture2D.frag");
	try
	{
		shader.charger();
		LOG(INFO) << "shader chargé avec succès.";
	}
	catch (const std::exception& e)
	{
		LOG(INFO) << "Erreur de chargement du shader : " << e.what();

	}
	glUseProgram(shader.getProgramID());

	GL::Texture text;
	text.loadFromFile("cat.png");
	glBindTexture(GL_TEXTURE_2D, text.TextureID);



	GLfloat triangle[] = {-1, 1,  1,1, -1,-1,  1, -1};
	GLfloat UVs[] = {0,1,  1,1, 0,0, 1,0};

	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 10.0f);
	float ratio = 1.0f;
	while (window.isOpen())
	{
		sf::Event event;
					while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
			window.close();

			switch (event.type)
			{
				case sf::Event::Closed:
				window.close();
				break;

				case sf::Event::KeyPressed:

				break;

				case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				ratio = float(event.size.width) / float(event.size.height);
				if(ratio >= 1)
				projection = glm::ortho(-2.0f*ratio,2.0f*ratio,-2.0f,2.0f,-2.0f,10.0f);
				else
				projection = glm::ortho(-2.0f, 2.0f,-2.0f/ratio,2.0f/ratio,-2.0f,10.0f);
				break;

				default:
				break;
			}
		}

	glClearColor(0, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangle);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, UVs);
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projection));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
	}

	return 0;
}
