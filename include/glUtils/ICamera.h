#ifndef DEF_CAMERINTERFACE
#define DEF_CAMERINTERFACE


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

enum class CameraDirection : char {UP, DOWN, LEFT, RIGHT, TOP, BOTTOM};

namespace glUtils {


    struct ICamera
    {
        virtual ~ICamera(){};

        virtual void orienter(float xRel, float yRel) = 0;
        virtual glm::mat4 lookAt() = 0;
        virtual void setTarget(glm::vec3 pos) = 0;
        virtual void deplacer(CameraDirection direction) = 0;



    };

}
#endif
