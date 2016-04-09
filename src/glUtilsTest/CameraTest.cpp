#include <boost/test/unit_test.hpp>


#include "glUtils/Camera.h"
#include "glUtilsTesting/testHelper.hpp"

BOOST_AUTO_TEST_SUITE(Camera)

BOOST_AUTO_TEST_CASE( Constructed_Camera_Equals_lookAt )
{

	std::vector<LOOKAT_PARAMETERS> valuesToCheck;
	valuesToCheck.push_back(LOOKAT_PARAMETERS(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0)));
	valuesToCheck.push_back(LOOKAT_PARAMETERS(glm::vec3(3,5,3), glm::vec3(37, -50, 6), glm::vec3(0,1,0)));

	for (const auto &e : valuesToCheck)
	{
		glm::mat4 expected = glm::lookAt(e.pos, e.target, e.axis);
		glUtils::Camera camera(e.pos, e.target, e.axis);
		glm::mat4 actual = camera.lookAt();
		if(!sameMatrix(actual, expected, 0.01f))
		{
			std::ostringstream ss;
			ss << "Bad Camera Ctor : " << vecToString(e.pos) << ", " << vecToString(e.target) << ", " << vecToString(e.axis) << ".";
			BOOST_ERROR(ss.str());
		}

	}


}

BOOST_AUTO_TEST_CASE (autofail)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()

