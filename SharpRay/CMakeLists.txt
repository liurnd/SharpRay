PROJECT(SharpRay)
cmake_minimum_required(VERSION 2.8)

FILE(GLOB_RECURSE RENDER_CPP "render/*.cpp")
FILE(GLOB_RECURSE MGR_CPP "manager/*.cpp")

macro (newTest testName)
	add_executable(${testName} "test/unittest_${testName}.cpp" ${RENDER_CPP} ${MGR_CPP})
	add_test(${testName} ${testName})
endmacro(newTest testName)

if (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/manager ${CMAKE_SOURCE_DIR}/render ${CMAKE_SOURCE_DIR}/third-party)

add_executable(sharpRay "test/main.cpp" ${RENDER_CPP} ${MGR_CPP})

newTest(obj)
