#include "glUtils/Camera.h"
#include <iostream>

namespace glUtils
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& pointCible, const glm::vec3& axeVertical) :  m_theta(-135), m_phi(-35.26), m_orientation(), m_axeVertical(axeVertical),
																					  m_deplacementLateral(), m_position(position), m_pointCible(pointCible)
	{
        orienter (0, 0);
	}
	Camera::~Camera()
	{

	}

	void Camera::orienter(float xRel, float yRel)
	{


		m_phi += -yRel * 0.5;
		m_theta += -xRel * 0.5;

		if(m_phi == 90.0)
			m_phi += -yRel * 0.5;

		else if(m_phi == -90.0)
			m_phi += yRel * 0.5;


		float phiRadian = m_phi * M_PI / 180;
		float thetaRadian = m_theta * M_PI / 180;


		if(m_axeVertical.x == 1.0)
		{
			m_orientation.x = sin(phiRadian);
			m_orientation.y = cos(phiRadian) * cos(thetaRadian);
			m_orientation.z = cos(phiRadian) * sin(thetaRadian);
		}


		else if(m_axeVertical.y == 1.0)
		{
			m_orientation.x = cos(phiRadian) * sin(thetaRadian);
			m_orientation.y = sin(phiRadian);
			m_orientation.z = cos(phiRadian) * cos(thetaRadian);
		}

		else
		{
			m_orientation.x = cos(phiRadian) * cos(thetaRadian);
			m_orientation.y = cos(phiRadian) * sin(thetaRadian);
			m_orientation.z = sin(phiRadian);
		}


		// Computing normal (which is used for lateral moves)

		m_deplacementLateral = glm::normalize(glm::cross(m_axeVertical, m_orientation));
		m_pointCible = m_position + m_orientation;

	}


	glm::mat4 Camera::lookAt()
	{
		return glm::lookAt(m_position, m_pointCible, m_axeVertical);
	}

	void Camera::deplacer(CameraDirection direction)
	{

        if(direction == CameraDirection::UP)
		{
			m_position = m_position + m_orientation * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
		else if(direction == CameraDirection::DOWN)
		{
			m_position = m_position - m_orientation * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
		else if(direction == CameraDirection::LEFT)
		{
			m_position = m_position + m_deplacementLateral * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
		else if(direction == CameraDirection::RIGHT)
		{
			m_position = m_position - m_deplacementLateral * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
		else if(direction == CameraDirection::TOP)
		{
			m_position = m_position + m_axeVertical * 0.5f;
			m_pointCible = m_position + m_orientation;

		}
		else if(direction == CameraDirection::BOTTOM)
		{
			m_position = m_position - m_axeVertical * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
	}
}
