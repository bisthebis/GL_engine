#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>


enum class CameraDirection : char {UP, DOWN, LEFT, RIGHT, TOP, BOTTOM};

namespace glUtils
{

	class Camera
	{
	    friend bool TEST_Camera() noexcept;


		public:
			Camera() = delete;
			Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);
			virtual ~Camera();

			void orienter(float xRel, float yRel); //TO CHECK (LOOKS OK)
			void lookAt(glm::mat4 &modelview); //OK
			void setCible(glm::vec3 pointCible); //TODO
			void deplacer(CameraDirection direction); //OK
			void computeAngles(); //TO REDO
			void DEBUG() {std::cout << m_orientation.x << '-' << m_orientation.y << '-' << m_orientation.z << std::endl;};

		private:

			float m_theta, m_phi; //Theta = horizontal axe, Phi = vertical axe
			const glm::vec3 m_axeVertical;

			glm::vec3 m_orientation;
			glm::vec3 m_deplacementLateral;
			glm::vec3 m_position;
			glm::vec3 m_pointCible;
	};
}
#endif // CAMERA_H
