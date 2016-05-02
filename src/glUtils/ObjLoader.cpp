#include "glUtils/ObjLoader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyException.h"

struct VERTEX
{
    glm::vec3 position;
    glm::vec2 UV;
    glm::vec3 normal;
};


namespace glUtils
{
    unsigned int loadModel(const char* name)
    {

      std::ifstream file;
      file.open(name);
      if(!file.is_open())
        throw MyException("File not found");

      std::size_t n_vertices(0), n_faces(0);
      std::string line;
      while(std::getline(file, line))
      {
          if(line[0] == 'f')
              ++n_faces;
      }
      std::vector<VERTEX> faces(0);
      std::vector<glm::vec3> positions(0);
      std::vector<glm::vec2> UVs(0);
      std::vector<glm::vec3> normals(0);
      file.clear();
      file.seekg(0, std::ios::beg);

      while(std::getline(file, line))
      {
          if (line[0] == 'v' && line[1] == ' ') //Position;
          {
              glm::vec3 vec;
              line[0] = ' ';
              std::istringstream ss(line);
              ss >> vec.x >> vec.y >> vec.z;
              positions.push_back(vec);
          }
          else if (line[0] == 'v' && line[1] == 't') //UVs;
          {
              glm::vec2 vec;
              line[0] = ' ';
              line[1] = ' ';
              std::istringstream ss(line);
              ss >> vec.x >> vec.y;
              UVs.push_back(vec);
          }
          else if (line[0] == 'v' && line[1] == 'n') //Normal;
          {
              glm::vec3 vec;
              line[0] = ' ';
              line[1] = ' ';
              std::istringstream ss(line);
              ss >> vec.x >> vec.y >> vec.z;
              normals.push_back(vec);
          }
          else if (line[0] == 'f')
          {
              std::replace_if(line.begin(), line.end(), [](char c){return (c=='/' || c=='f');}, ' ');
              int indices[9] = {0};
              std::istringstream ss(line);

              //std::cout << "Numbers of pos, UV, norm : " << positions.size() << ' ' << UVs.size() << ' ' << normals.size() << std::endl;
              for (int i = 0; i < 8; ++i)
              {
                  ss >> indices[i];
                  //std::cout << indices[i] << ' ';
              }

              //std::cout << std::endl;
              VERTEX vertex[3];
              vertex[0].position = positions[indices[0]-1];
              vertex[0].UV = UVs[indices[1]-1];
              vertex[0].normal = normals[indices[2]-1];

              vertex[1].position = positions[indices[3]-1];
              vertex[1].UV = UVs[indices[4]-1];
              vertex[1].normal = normals[indices[5]-1];

              vertex[2].position = positions[indices[6]-1];
              vertex[2].UV = UVs[indices[7]-1];
              vertex[2].normal = normals[indices[8]-1];


              faces.push_back(vertex[0]);
              faces.push_back(vertex[1]);
              faces.push_back(vertex[2]);

          }
      }

      ///Now, faces should be a correct array of floats, packed as vectors themselves packed as vertex

      GLuint VBO = 0;
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      glBufferData(GL_ARRAY_BUFFER, faces.size()*8*sizeof(float), faces.data(), GL_STATIC_DRAW);


      return VBO;
    }
}
