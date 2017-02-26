PROJECT(MyTestingExample)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()
INCLUDE_DIRECTORIES(src)

OPTION(BUILD_TEST "Build the tests" FALSE)

ADD_LIBRARY(epi
        src/binary_tree.cpp
        src/binary_tree.h)

IF(BUILD_TEST)
	ADD_EXECUTABLE(epi_test test/binary_tree_test.cpp)
	TARGET_LINK_LIBRARIES(epi_test epi ${CONAN_LIBS})
ENDIF()
