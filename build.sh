#!/bin/bash
#
# Generic script to build project with CMake
printf "Creating build directory...\n"
mkdir ./build
sync
sleep 1
cd ./build
printf "Starting generation of build files with CMake...\n"
cmake ..
printf "\nBuild files created.\nIf no errors were reported above then run: cd build ; make\n\n"
