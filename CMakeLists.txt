# cmake build file for: weather
#  created 31 Jul 2019
#  To use run:  mkdir build && cd build && cmake .. && make
#
# min cmake version was 3.13. Set for GitHub version: 3.12.4
# Curl version message requires version >= 3.13
cmake_minimum_required(VERSION 3.13)
project(weather)
#
# enable verbose output
#set(CMAKE_VERBOSE_MAKEFILE on)
#
# add location for built binary file
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#
# add list of c source code files to var ${SOURCES}
file(GLOB SOURCES "./src/*.c")
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

#
# Try to build if Curl libs are found...
if(CURL_FOUND)
    # get the location of the Curl include location
    include_directories(${CURL_INCLUDE_DIRS})
    # list the names of the C libraries to link against: libcurl
    target_link_libraries(weather ${CURL_LIBRARIES})
    # output what verison of Curl lib was found
    message("Found Curl library version ${CURL_VERSION_STRING}.")
else(CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

