cmake_minimum_required (VERSION 2.6)
project (Experiments)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH}) #SFML Package doesn't tell CMAKE how to find the lib, so FindSFML.cmake is required


find_package(SFML 2 REQUIRED system window graphics)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Get Boost
find_package ( Boost COMPONENTS unit_test_framework )

include_directories(${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
include_directories(include)


add_executable(
	App

	src/real_main.cpp

	src/MyException.cpp

	src/glUtils/Camera.cpp
	src/glUtils/RawModel.cpp
	src/glUtils/Shader.cpp
	src/glUtils/Texture.cpp

	include/MyException.h

	include/glUtils/Camera.h
	include/glUtils/RawModel.h
	include/glUtils/Shader.h
	include/glUtils/Texture.h

)
target_link_libraries(App ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES})

#if (Boost_FOUND)
	add_executable(
		Tests

		src/test_main.cpp

		include/glUtilsTest/testHelper.h

		src/glUtilsTest/CameraTest.cpp
		src/glUtilsTest/TrivialTest.cpp
		src/glUtilsTest/testHelper.cpp

		src/MyException.cpp
		src/glUtils/Camera.cpp
		src/glUtils/RawModel.cpp
		src/glUtils/Shader.cpp
		src/glUtils/Texture.cpp

	)


	target_link_libraries(Tests ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES})
#endif()
