################################################################################
### Copyrights (c) 2015
### Marwan Abdellah < abdellah.marwan@gmail.com >
################################################################################

# OpenCL-based Fourier Volume Rendering
project( oclFVR )

# Set the minimum version of CMake to be able to run the application
cmake_minimum_required( VERSION 2.8 )

### Add CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

message($ENV{QTDIR})
if( APPLE )
    # Check if environment variable QTDIR is set.
    # Extra security for windows environment as well.
    if( DEFINED ENV{QTDIR} )
        set( CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH} )
    else()
        message( FATAL_ERROR "ERROR: Environment variable QTDIR is not set. Please locate your Qt folder QT5DIR." )
    endif ()
endif()

### Dependencies
include( OpenGL )
include( Qt )
include( OpenCL)

# Add the binary directory to the include and set off the mocs.
include_directories( ${PROJECT_BINARY_DIR} )

# Add the src directory to the CMake tree and set the source/header/ui files
set( CL_FVR_SOURCES )
set( CL_FVR_HEADERS )

add_subdirectory( src )
