#!/bin/bash

# Check if the program exists in the build directory
if [ -f "build/main" ] || [ -f "build/main.exe" ]; then
    # Run the program
    ./build/main || ./build/main.exe
else
    echo "Program not built yet. Run build.sh first."
fi