# Add the source files to the CMake tree
#list( APPEND CL_FVR_SOURCES
#    systems/ParticleSystem.cpp
#    systems/CPUParticleSystem.cpp
#    systems/GPUParticleSystem.cpp
#)

# Add the header files to the CMake tree
list( APPEND CL_FVR_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Headers.hh
)

# Include the directories to the CMake source tree
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/common )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/rendering )

# Add the applications 
add_subdirectory( apps )

