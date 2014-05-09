PROJECT(SharpRay)
cmake_minimum_required(VERSION 2.8)
FILE(GLOB_RECURSE SRC_CPP "src/*.cpp")
FILE(GLOB_RECURSE SRC_H "src/*.h")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/third-party)

add_executable(sharpRay ${SRC_CPP} ${SRC_H})
