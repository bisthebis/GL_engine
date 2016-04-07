#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>


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

			void orienter(float xRel, float yRel);
			void lookAt(glm::mat4 &modelview);

			void deplacer(CameraDirection direction);

		protected:
		private:
		    ///Updated 7 april
		    void computeAngles();

			float m_theta, m_phi; //Theta = horizontal axe, Phi = vertical axe
			glm::vec3 m_orientation;


			const glm::vec3 m_axeVertical;
			glm::vec3 m_deplacementLateral;

			glm::vec3 m_position;
			glm::vec3 m_pointCible;
	};
}
#endif // CAMERA_H
