#include "glUtils/Camera.h"
#include "easylogging++.h"
#include "MyException.h"

#include <iostream>


#define ENSURE(predicate, error) if(!(predicate)) {LOG(ERROR) << "ENSURE failed : " << error; throw MyException(error);}

namespace TEST
{
    using glm::mat4;
    using glm::vec3;
    using glm::lookAt;
    using glUtils::Camera;
    using std::cerr;
    using std::endl;

    void check_camera_equals_lookat(glm::vec3 pos, glm::vec3 eye, glm::vec3 vert);

    bool TEST_Camera() noexcept
    {



        ///Ensure that two same parameters Camera with different target are different
        try
        {
            Camera camera1(vec3(5,7,3), vec3(7,6,87),vec3(1,0,0));
            Camera camera2(vec3(5,7,3), vec3(-50, 70, 65),vec3(1,0,0));
            mat4 first, second;
            camera1.lookAt(first); camera2.lookAt(second);
            ENSURE(first != second, " pointCible is unused !");
            LOG(INFO) << "pointCible is correctly used. Test is OK";
        }
        catch (const std::exception& e)
        {
            cerr << "Exception dans le test : " << e.what() << endl;
        }

        check_camera_equals_lookat(glm::vec3(5,7,3), glm::vec3(17,-90.5,32), glm::vec3(1,0,0)); ///broken
        check_camera_equals_lookat(glm::vec3(5,7,3), glm::vec3(17,-90.5,32), glm::vec3(0,1,0)); ///OK
        check_camera_equals_lookat(glm::vec3(5,7,3), glm::vec3(17,-90.5,32), glm::vec3(0,0,1)); ///broken

        check_camera_equals_lookat(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(1,0,0)); ///OK
        check_camera_equals_lookat(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); ///OK
        check_camera_equals_lookat(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,0,1)); ///OK



        return true;
    }



    void check_camera_equals_lookat(glm::vec3 pos, glm::vec3 eye, glm::vec3 vert)
    {
        ///Ensure that for a valid axis, a recently constructed Camera outputs the same matrix as glm::LookAt
        Camera valide1(pos, eye, vert);
        mat4 Expected = lookAt(pos, eye, vert);
        mat4 Actual; valide1.lookAt(Actual);
        try
        {
                    mat4 difference = Expected - Actual;
                    bool smallDiff = true;
                    for(float* ptr = glm::value_ptr(difference); ptr != glm::value_ptr(difference) + 16; ++ptr)
                        if(*ptr > 0.1 || *ptr < -0.1) smallDiff = false;
                    ENSURE(smallDiff, "Constructed Cameras aren't correct !");
                    LOG(INFO) << "Freshly constructed Cameras are correct. Test is OK";

        }
        catch (const std::exception& e)
        {
            cerr << "Exception dans le test : " << e.what() << endl;
            for (int i = 0; i < 16; ++i)
            {
                const float* actual = glm::value_ptr(Actual);
                const float* expected = glm::value_ptr(Expected);
                LOG(ERROR) << "Actual vs Expected, number " << i << " : " << actual[i] << ' ' << expected[i] << ". Difference : " << actual[i] - expected[i];
            }
        }
    }
}
