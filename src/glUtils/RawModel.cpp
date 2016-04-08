#include <GL/glew.h>
#include <GL/gl.h>


#include "glUtils/RawModel.h"

#include "MyException.h"


namespace glUtils
{

  RawModel::RawModel() : VBOs(0) {}
  RawModel::~RawModel() {this->cleanup();}
  void RawModel::cleanup()
  {
    if(glIsVertexArray(VAO))
    {
      glDeleteVertexArrays(1, &VAO);
    }


    VAO = 0;

    for (GLuint& VBO : VBOs)
    {
      if(glIsBuffer(VBO))
      {
        glDeleteBuffers(1, &VBO);
      }


      VBO = 0;
    }
  }

  void RawModel::bindVAO() const
  {
    glBindVertexArray(VAO);
  }

  void RawModel::setVAO(GLuint val)
  {
    this->VAO = val;
  }

  void RawModel::pushVBO(GLuint val)
  {
    VBOs.push_back(val);
  }


}
