# cmake build file for: weather
#  created 31 Jul 2019
#  To use run:  mkdir build && cd build && cmake .. && make
#
# min cmake version was 3.13. Set for GitHub version: 3.12.4
cmake_minimum_required(VERSION 3.12)
project(weather)
#
# enable verbose output
#set(CMAKE_VERBOSE_MAKEFILE on)
#
# add list of c source code files to var ${SOURCES}
file(GLOB SOURCES "./*.c")
#
# add additional flags to standard ${CMAKE_C_FLAGS}
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
# add compiler requirements for the gcc compiler
add_definitions(-std=gnu11)
#
# give final executable name and the C source code files required to build it
add_executable(weather ${SOURCES})
#
# state what libraries we need to compile
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
#
# list the names of the C libraries to link against: libcurl
target_link_libraries(weather ${CURL_LIBRARIES})
