#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <vector>
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

inline void getProjection(glm::mat4& target, float width, float height, bool orthographic = false)
{
		if(!orthographic)
			target = glm::perspective(60.0f, width/height, -1.0f, 100.0f);
		else
			{
				float ratio = width / height;
				if(ratio >= 1)
				target = glm::ortho(-2.0f * ratio, 2.0f * ratio, -2.0f, 2.0f, -2.0f, 100.0f);
				else
				target = glm::ortho(-2.0f, 2.0f, -2.0f / ratio, 2.0f / ratio, -2.0f, 100.0f);
			}
}

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
	glEnable(GL_DEPTH_TEST);


	GL::Shader shader("Shaders/Color3D.vert", "Shaders/Color3D.frag");
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


	//GLfloat vertices[] = {-1,1,0, 0,1,1,  1,1,0, 1,1,0  -1,-1,0, 0,0, 1,-1,0, 1,0,1};
	/*GLfloat vertices[] ={1,1,1,  1,1,1
		1,1,0,  1,0,1,
		1,0,1,  1,1,0

	};*/
	std::vector<GLfloat> vertices(0);

	{
		float vertice[] = {-1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1

                    -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1


                    1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2

                    1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2


                    -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3

                    -1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0};   // Face 3


										float couleurs[] = {1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1
								                    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1

								                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2
								                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2

								                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3
								                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0};          // Face 3
			float* vertptr = vertice;
			float* colptr = couleurs;
			for (int i = 0; i < 108; i += 6)
			{


					vertices.push_back(*vertptr++);
					vertices.push_back(*vertptr++);
					vertices.push_back(*vertptr++);
					vertices.push_back(*colptr++);
					vertices.push_back(*colptr++);
					vertices.push_back(*colptr++);

			}

			for (auto e : vertices)
			std::cout << e << ' ';

	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 10.0f);
	glm::mat4 view;

	Camera camera(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,0,1));
	camera.lookAt(view);

	bool run = true;
	bool orthographic = false;
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
							break;

						case sf::Keyboard::Key::P:
							orthographic = !orthographic;

						default:
							break;
					}

				break;

				case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);


				default:
				break;
			}
		}

	glClearColor(0, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (char*)nullptr + 12 );
	glEnableVertexAttribArray(1);

	getProjection(projection, window.getSize().x, window.getSize().y, orthographic);
	camera.lookAt(view);
	//view = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,0,1));

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view));
	glDrawArrays(GL_TRIANGLES, 0, 18);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	window.display();
	}

	glDeleteBuffers(1, &VBO);

	return 0;
}
