#include <GL/glew.h>
#include <GL/gl.h>

#include "easylogging++.h"
#include "RawModel.h"
#include "MyException.h"

namespace GL
{

  RawModel::RawModel() : VBOs(0) {LOG(INFO) << "Creating a RawModel";}
  RawModel::~RawModel() {this->cleanup();}
  void RawModel::cleanup()
  {
    if(glIsVertexArray(VAO))
    {
      LOG(INFO) << "Deleting a VAO : " << VAO;
      glDeleteVertexArrays(1, &VAO);
    }


    VAO = 0;

    for (GLuint& VBO : VBOs)
    {
      if(glIsBuffer(VBO))
      {
        LOG(INFO) << "Deleting a VBO : " << VBO;
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
