################################################################################
### Copyrights (c) 2015
### Marwan Abdellah <abdellah.marwan@gmail.com>
################################################################################

# Project name 
project( clFVR )

# Set the minimum version of CMake to be able to run the application
cmake_minimum_required( VERSION 2.8 )

### Add CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

### Dependencies
include( OpenGL )
include( Qt )

# Add the binary directory to the include and set off the mocs.
include_directories( ${PROJECT_BINARY_DIR} )

# Add the src directory to the CMake tree and set the source/header/ui files
set( CL_FVR_SOURCES )
set( CL_FVR_HEADERS )

add_subdirectory( src )
