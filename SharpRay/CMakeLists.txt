PROJECT(SharpRay)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
SUBDIRS(render manager third-party/getopt)

macro (newTest testName)
    add_executable("unittest_${testName}" "test/unittest_${testName}.cpp" ${MGR_CPP})
	TARGET_LINK_LIBRARIES("unittest_${testName}" libsharpray libsharpray_mgr)
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

newTest(obj)
newTest(faceReader)
