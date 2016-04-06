cmake_minimum_required (VERSION 2.6)
project (Experiments)

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
