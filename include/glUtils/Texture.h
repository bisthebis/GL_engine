#ifndef DEF_TEXTURE_H
#define DEF_TEXTURE_H


#include <string>

namespace glUtils
{
  class Texture
  {
    using GLuint = unsigned int;
    private:
       GLuint TextureID = 0;
    public:
      Texture(){}
      ~Texture();
      void loadFromFile(const std::string& src);
      GLuint getProgramID();

  };

}

#endif
