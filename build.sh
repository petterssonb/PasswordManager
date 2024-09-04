#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to generate build files
cmake ..

# Build the project using CMake
cmake --build .

# Go back to the root directory
cd ..