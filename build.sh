#!/bin/bash
#
# Generic script to build project with CMake

if [ -d ./build ] ; then
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
if [ $? ] ; then
  printf "CMake ran Ok - start build with 'make' ...\n"
  make
  if [ $? ] ; then
    printf "\nExecuting built application:\n\n"
    ../bin/weather
  fi
 printf "\nBuild completed.\nIf no errors were reported - see compiled binary in sub directory:  bin/\n\n"
else
  printf "\nBuild files created.\nCMake errors were reported. See above or try to run: cd build ; make\n\n"
fi
