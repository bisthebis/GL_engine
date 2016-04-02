#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <SFML/Window.hpp>

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


	GLfloat triangle[] = {0, 0, 0.5, -0.5, -0.5, -0.5};

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

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	window.display();
	}

	return 0;
}
