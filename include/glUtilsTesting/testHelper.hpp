#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <algorithm>

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
