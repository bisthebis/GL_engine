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
#include "../include/Camera.h"

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


	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	GLfloat vertices[] = {-1,1,0,1,  1,1,1,1,  -1,-1,0,0, 1,-1,1,0};
	glBufferData(GL_ARRAY_BUFFER, 16*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 10.0f);
	glm::mat4 view;

	Camera camera(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,0,1));
	camera.lookAt(view);
	float ratio = 1.0f;
	bool run = true;
	while (run)
	{
		sf::Event event;
					while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape))
			run = false;

			switch (event.type)
			{
				case sf::Event::Closed:
				run = false;
				break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Key::Z:
							camera.deplacer(CameraDirection::UP);
							break;
						case sf::Keyboard::Key::S:
							camera.deplacer(CameraDirection::DOWN);
							break;
						case sf::Keyboard::Key::Q:
							camera.deplacer(CameraDirection::LEFT);
							break;
						case sf::Keyboard::Key::D:
							camera.deplacer(CameraDirection::RIGHT);
							break;
						case sf::Keyboard::Key::C:
							camera.deplacer(CameraDirection::BOTTOM);
							break;
						case sf::Keyboard::Key::X:
							camera.deplacer(CameraDirection::TOP);

						default:
							break;
					}

				break;

				case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				ratio = float(event.size.width) / float(event.size.height);
				if(ratio >= 1)
				projection = glm::ortho(-2.0f * ratio, 2.0f * ratio, -2.0f, 2.0f, -2.0f, 10.0f);
				else
				projection = glm::ortho(-2.0f, 2.0f, -2.0f / ratio, 2.0f / ratio, -2.0f, 10.0f);
				break;

				default:
				break;
			}
		}

	glClearColor(0, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (char*)nullptr + 8 );
	glEnableVertexAttribArray(1);

	camera.lookAt(view);

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
	}

	glDeleteBuffers(1, &VBO);

	return 0;
}
