#!/bin/sh
# Automatic compilation script by CMake using CMakeLists.txt
# "Execute the file using sh, the Bourne shell, 
#	or a compatible shell"

# Remove residues
echo "Clearing residues..."
rm CMakeCache.txt
rm Makefile
rm cmake_install.cmake
rm -rf CMakeFiles

# Compile
echo "Compiling..."
cmake . && make 

# Remove residues
echo "Clearing residues..."
rm CMakeCache.txt
rm Makefile
rm cmake_install.cmake
rm -rf CMakeFiles

echo "Done!"