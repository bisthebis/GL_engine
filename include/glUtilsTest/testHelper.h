#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>


struct LOOKAT_PARAMETERS
{
		glm::vec3 pos;
		glm::vec3 target;
		glm::vec3 axis;
		LOOKAT_PARAMETERS(glm::vec3 pos, glm::vec3 target, glm::vec3 axis);
};
bool sameMatrix(const glm::mat4& lhs, const glm::mat4& rhs, float precision);
std::string vecToString(glm::vec3 src);
