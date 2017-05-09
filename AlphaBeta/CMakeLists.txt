cmake_minimum_required(VERSION 3.6)
project(Heuristic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	AlphaBeta.cpp
	AlphaBeta.hpp
	Point.hpp
	Test.cpp)

add_executable(AlphaBeta ${SOURCE_FILES})
