# Update the current directory to resolve the multi-level CMake configuration
set( CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

# Add the source files to the CMake tree
list( APPEND CL_FVR_SOURCES
    data/ComplexImage.cpp
    data/ComplexImage.ipp
    data/ComplexVolume.cpp
    data/ComplexVolume.ipp
    data/Image.cpp
    data/Image.ipp
    data/Volume.cpp
    data/Volume.ipp
    fft/FFT.cpp
    fft/FFTShift.cpp
    geometry/Vector2.cpp
    geometry/Vector2.ipp
    geometry/Vector3.cpp
    geometry/Vector3.ipp
    rendering/AbstractRenderer.cpp
)

# Add the header files to the CMake tree
list( APPEND CL_FVR_HEADERS
    common/Headers.hh
    common/Typedefs.hh
    data/ComplexImage.h
    data/ComplexVolume.h
    data/Image.h
    data/Volume.h
    fft/FFT.h
    fft/FFTShift.h
    geometry/Vector2.h
    geometry/Vector3.h
    rendering/AbstractRenderer.h
)

# Include the directories to the CMake source tree
include_directories( common )
include_directories( data )
include_directories( fft )
include_directories( filters )
include_directories( geometry )
include_directories( opencl )
include_directories( rendering )
include_directories( system )

# Create a library with the main compoments of the framework and link the apps
# against it later to reduce the compilation time
set( CL_FVR_LIBRARY "CLFVR" )
add_library( ${CL_FVR_LIBRARY} ${CL_FVR_SOURCES} ${CL_FVR_HEADERS} )
set_property( TARGET ${CL_FVR_LIBRARY} PROPERTY IMPORTED_LOCATION
    ${CMAKE_BINARY_DIRECTORY}/lib${CL_FVR_LIBRARY}.a )

install( TARGETS ${CL_FVR_LIBRARY} DESTINATION lib )
install( FILES ${CL_FVR_HEADERS} DESTINATION include )

# Add the applications 
add_subdirectory( apps )

