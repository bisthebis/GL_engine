#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glUtils/Shader.h"
#include "glUtils/Texture.h"
#include "glUtils/Camera.h"
#include "glUtils/RawModel.h"

#include "luaApi/LuaApi.h"

#include "MyException.h"
#include "LuaState.h"

using std::cout;
using std::endl;

inline void getProjection(glm::mat4& target, float width, float height, bool orthographic = false, const float zFar = 50.0f)
{
		if(!orthographic)
			target = glm::perspective(45.0f, width/height, 0.1f, zFar);
		else
			{
				float ratio = width / height;
				if(ratio >= 1)
				target = glm::ortho(-2.0f * ratio, 2.0f * ratio, -2.0f, 2.0f, -2.0f, zFar);
				else
				target = glm::ortho(-2.0f, 2.0f, -2.0f / ratio, 2.0f / ratio, -2.0f, zFar);
			}
}


void initCube(glUtils::RawModel& model);

bool orthographic = false; /*Lua Globals declared in LuaApi.h */
bool run = true;
glUtils::Camera *global_camera = nullptr;

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	sf::Clock time;

    //Read window size from Lua : config.lua

    glUtils::Camera camera(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,0,1));
    global_camera = &camera;


    int width(500), height(500);

        LuaState Lua;
        luaL_dofile(Lua(), "config.lua");
        lua_register(Lua(), "getCamera", &Lua_API_getCamera);
        lua_register(Lua(), "getProjectionType", &Lua_API_getProjectionType);
        lua_register(Lua(), "switchProjectionType", &Lua_API_switchProjectionType);
        lua_register(Lua(), "pushCamera", &Lua_API_moveCamera);
        lua_register(Lua(), "rotateCamera", &Lua_API_rotateCamera);
				lua_register(Lua(), "quit", &Lua_API_stopRunning);

        Lua.doProcedure("init");

        lua_getglobal(Lua(), "width");
        lua_getglobal(Lua(), "height");
        width = lua_tointeger(Lua(), -2);
        height = lua_tointeger(Lua(), -1);





    sf::Window window(sf::VideoMode(width, height), "OpenGL works!", sf::Style::Default, settings);
	glewInit();
	glEnable(GL_DEPTH_TEST);

	glUtils::RawModel cube;
	initCube(cube);


	glUtils::Shader shader("Shaders/Texture3D.vert", "Shaders/Texture2D.frag");
	shader.charger();
	glUseProgram(shader.getProgramID());

	glUtils::Texture text, text2;
	text.loadFromFile("container.png");
	text2.loadFromFile("cat.png");

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 10.0f);
	glm::mat4 view;
	glm::mat4 models[5];
	for (int i = 0; i < 5; ++i)
	{
		models[i] = glm::mat4(1.0f);
		models[i] = glm::translate(models[i], glm::vec3(1.5f * i - 3.0f, 0.5f*i, 0));
		models[i] = glm::rotate(models[i], i * 20.0f - 40.0f, glm::vec3(0.5f, 0.5f, 0.5f));
	}




	getProjection(projection, window.getSize().x, window.getSize().y, orthographic);
	while (run)
	{
		sf::Event event;
        while (window.pollEvent(event))
		{


			switch (event.type)
			{
				case sf::Event::Closed:
				run = false;
				break;

				case sf::Event::KeyPressed:
                    lua_getglobal(Lua(), "handleKey"); ///Let Lua handle keyboard
                    lua_pushinteger(Lua(), event.key.code);
                    lua_pcall(Lua(), 1, 0, 0);

				break;

				case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				getProjection(projection, window.getSize().x, window.getSize().y, orthographic);
                break;


				default:
				break;
            }
		}

    glClearColor(0, 0.5, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cube.bindVAO();

    view = camera.lookAt();
    getProjection(projection, window.getSize().x, window.getSize().y, orthographic);

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view));

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "myTexture"), 0);
	glBindTexture(GL_TEXTURE_2D, text.getProgramID());
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(shader.getProgramID(), "myTexture2"), 1);
	glBindTexture(GL_TEXTURE_2D, text2.getProgramID());

    glUniform1f(3, std::max(0.5f + 0.5f*sin(time.getElapsedTime().asSeconds()), 0.0));


	for (int i = 0; i < 5; ++i)
	{
			glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(models[i]));
			glDrawArrays(GL_TRIANGLES, 0, 36);
	}



    window.display();
	}


	return 0;
}


void initCube(glUtils::RawModel& model)
{
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (char*)nullptr + 12 );
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		model.setVAO(VAO);
		model.pushVBO(VBO);
}
