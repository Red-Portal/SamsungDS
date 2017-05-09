cmake_minimum_required(VERSION 3.6)
project(Heuristic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	heuristic.hpp
	heuristic.cpp
	test.cpp)

add_executable(heuristic ${SOURCE_FILES})
