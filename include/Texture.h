#ifndef DEF_TEXTURE_H
#define DEF_TEXTURE_H


#include <string>

namespace GL
{
  class Texture
  {
    using GLuint = unsigned int;
    public:
       GLuint TextureID = 0;
    public:
      Texture(){}
      ~Texture();
      void loadFromFile(const std::string& src);

  };

}

#endif
