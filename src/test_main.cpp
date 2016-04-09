#define BOOST_TEST_MODULE GLOBAL_TEST
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "glUtils/Camera.h"
#include "glUtilsTesting/testHelper.hpp"



BOOST_AUTO_TEST_CASE( Constructed_Camera_Equals_lookAt )
{
	glm::mat4 expected[2], actual[2];

	expected[0] = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glUtils::Camera camera0(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
	camera0.lookAt(actual[0]);
	BOOST_CHECK(sameMatrix(actual[0], expected[0], 0.01f));

	expected[1] = glm::lookAt(glm::vec3(3,5,3), glm::vec3(37, -50, 6), glm::vec3(0,1,0));
	glUtils::Camera camera1(glm::vec3(3,5,3), glm::vec3(37, -50, 6), glm::vec3(0,1,0));
	camera1.lookAt(actual[1]);
	BOOST_CHECK(sameMatrix(actual[1], expected[1], 0.01f));
}
