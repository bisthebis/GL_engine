#ifndef DEF_RAW_MODEL_H
#define DEF_RAW_MODEL_H

#include <vector>

namespace GL
{

  class RawModel
  {
      using GLuint = unsigned int;

    public:
      GLuint VAO = 0;
      std::vector<GLuint> VBOs;

    public:
      RawModel();
      ~RawModel();
      void cleanup();

      void bindVAO() const;
      void setVAO(GLuint ID);
      void pushVBO(GLuint ID);

  };

}


#endif
