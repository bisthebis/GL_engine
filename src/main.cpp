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

	sf::Clock time;

	sf::Window window(sf::VideoMode(200, 200), "OpenGL works!", sf::Style::Default, settings);
	glewInit();

	Shader shader("Shaders/color2D.vert", "Shaders/color2D.frag");
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

	GLfloat triangle[] = {0, 0, 0.5, -0.5, -0.5, -0.5};
	GLfloat color[] = {1,0,0,
										0,1,0,
										0,0,1};

	glm::vec2 translation(0,1);


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

				default:
				break;
			}
		}

	glClearColor(0, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangle);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color);
	glEnableVertexAttribArray(1);

	translation.x = 0.5*sin(time.getElapsedTime().asSeconds());
	glUniform2f(0, translation.x, translation.y);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
	}

	return 0;
}
