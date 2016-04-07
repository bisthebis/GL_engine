#include "Camera.h"

namespace GL
{
	Camera::Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical) :  m_theta(-135), m_phi(-35.26), m_orientation(), m_axeVertical(axeVertical),
																					  m_deplacementLateral(), m_position(position), m_pointCible(pointCible)
	{
	  orienter (0, 0);
	}
	Camera::~Camera()
	{
		//dtor
	}

	void Camera::orienter(float xRel, float yRel)
	{
		// R�cup�ration des angles

		m_phi += -yRel * 0.5;
		m_theta += -xRel * 0.5;


		// Limitation de l'angle phi
	/*
		if(m_phi > 89.0)
			m_phi = 89.0;

		else if(m_phi < -89.0)
			m_phi = -89.0;

	//*///old en haut

		if(m_phi == 90.0)
			m_phi += -yRel * 0.5;

		else if(m_phi == -90.0)
			m_phi += yRel * 0.5;

		// Conversion des angles en radian

			float phiRadian = m_phi * M_PI / 180;
			float thetaRadian = m_theta * M_PI / 180;


			// Calcul des coordonn�es sph�riques

			m_orientation.x = cos(phiRadian) * sin(thetaRadian);
			m_orientation.y = sin(phiRadian);
			m_orientation.z = cos(phiRadian) * cos(thetaRadian);

			// Si l'axe vertical est l'axe X

			if(m_axeVertical.x == 1.0)
			{
				// Calcul des coordonn�es sph�riques

				m_orientation.x = sin(phiRadian);
				m_orientation.y = cos(phiRadian) * cos(thetaRadian);
				m_orientation.z = cos(phiRadian) * sin(thetaRadian);
			}


			// Si c'est l'axe Y

			else if(m_axeVertical.y == 1.0)
			{
				// Calcul des coordonn�es sph�riques

				m_orientation.x = cos(phiRadian) * sin(thetaRadian);
				m_orientation.y = sin(phiRadian);
				m_orientation.z = cos(phiRadian) * cos(thetaRadian);
			}


			// Sinon c'est l'axe Z

			else
			{
				// Calcul des coordonn�es sph�riques

				m_orientation.x = cos(phiRadian) * cos(thetaRadian);
				m_orientation.y = cos(phiRadian) * sin(thetaRadian);
				m_orientation.z = sin(phiRadian);
			}


			// Calcul de la normale

			m_deplacementLateral = glm::normalize(glm::cross(m_axeVertical, m_orientation));
			m_pointCible = m_position + m_orientation; ///Regarder vers le point 1 unit� + loin que la position

	}


	void Camera::lookAt(glm::mat4 &modelview)
	{
		// Actualisation de la vue dans la matrice

		modelview = glm::lookAt(m_position, m_pointCible, m_axeVertical);
	}

	void Camera::deplacer(CameraDirection direction)
	{

		if(direction == CameraDirection::UP)
		{
			m_position = m_position + m_orientation * 0.5f;
			m_pointCible = m_position + m_orientation;
		}


		// Recul de la cam�ra

		if(direction == CameraDirection::DOWN)
		{
			m_position = m_position - m_orientation * 0.5f;
			m_pointCible = m_position + m_orientation;
		}


		// D�placement vers la gauche

		if(direction == CameraDirection::LEFT)
		{
			m_position = m_position + m_deplacementLateral * 0.5f;
			m_pointCible = m_position + m_orientation;
		}


		// D�placement vers la droite

		if(direction == CameraDirection::RIGHT)
		{
			m_position = m_position - m_deplacementLateral * 0.5f;
			m_pointCible = m_position + m_orientation;
		}

		if(direction == CameraDirection::TOP)
		{
			m_position = m_position + m_axeVertical * 0.5f;
			m_pointCible = m_position + m_orientation;

		}

		if(direction == CameraDirection::BOTTOM)
		{
			m_position = m_position - m_axeVertical * 0.5f;
			m_pointCible = m_position + m_orientation;
		}
	}
}
