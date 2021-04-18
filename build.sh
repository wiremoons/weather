#!/bin/bash
#
# Generic script to build project with CMake

if [[ -d ./build ]] ; then
  printf "Found old build directory:  removing...\n"
  rm -Rf ./build
  sync
fi

printf "Creating build directory...\n"
mkdir ./build
sync
sleep 1
cd ./build
printf "Starting generation of build files with CMake...\n"
cmake ..
printf "\nBuild files created.\nIf no errors were reported above then run: cd build ; make\n\n"
