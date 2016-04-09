#include "glUtilsTest/testHelper.h"



LOOKAT_PARAMETERS::LOOKAT_PARAMETERS(glm::vec3 pos, glm::vec3 target, glm::vec3 axis) : pos(pos), target(target), axis(axis) {}

bool sameMatrix(const glm::mat4& lhs, const glm::mat4& rhs, float precision)
{
    if(precision < 0)
      precision *= -1;
    glm::mat4 difference = lhs - rhs;

    const float * ptr = glm::value_ptr(difference);
    const float * end = ptr + 16;
    for (; ptr != end; ++ptr)
    {
      if(std::abs(*ptr) > precision)
      return false;
    }


    return true;
}

std::string vecToString(glm::vec3 src)
{
  std::ostringstream ss;
  ss << '(' << src.x << ',' << src.y << ',' << src.z << ')';
  return ss.str();
}
