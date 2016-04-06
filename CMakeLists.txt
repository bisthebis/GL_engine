cmake_minimum_required (VERSION 2.6)
project (Experiments)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})



find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})



add_executable(
	Programme
	src/Camera.cpp
	src/main.cpp
	src/MyException.cpp
	src/RawModel.cpp
	src/Shader.cpp
	src/Texture.cpp

	include/Camera.h
	include/easylogging++.h
	include/MyException.h
	include/RawModel.h
	include/Shader.h
	include/Texture.h

)

target_link_libraries(Programme ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES})