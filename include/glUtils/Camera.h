#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>

#include "glUtils/ICamera.h"


namespace glUtils
{

    class Camera : public ICamera
	{
		public:
			Camera() = delete;
			Camera(const glm::vec3& position, const glm::vec3& pointCible, const glm::vec3& axeVertical);
			virtual ~Camera();

			void orienter(float xRel, float yRel);
			glm::mat4 lookAt();

			void deplacer(CameraDirection direction);
            void setTarget(glm::vec3 pos) {};

		protected:

			float m_theta, m_phi; //Theta = horizontal axe, Phi = vertical axe
			glm::vec3 m_orientation;


			glm::vec3 m_axeVertical;
			glm::vec3 m_deplacementLateral;

			glm::vec3 m_position;
			glm::vec3 m_pointCible;
	};


    ///TMP
    struct DebugCamera : public Camera
    {
        DebugCamera(const glm::vec3& position, const glm::vec3& pointCible, const glm::vec3& axeVertical) : Camera(position, pointCible, axeVertical) {}
        glm::mat4 lookAt(){return this->Camera::lookAt();}
    };
}
#endif // CAMERA_H
