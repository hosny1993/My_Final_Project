# Header files
FIND_PATH(OPENCL_INCLUDE_DIR
        NAMES
            CL/cl.h OpenCL/cl.h
        PATHS
            # AMD
            $ENV{AMD_OPENCL}/include

            # Intel
            $ENV{INTEL_OPENCL}/include
            /usr/include

            # NVIDIA
            $ENV{NVIDIA_OPENCL}/include
            $ENV{NVIDIA_GPU_COMPUTING_SDK_ROOT}/OpenCL/common/inc

            # Legacy ATI Stream SDK
            $ENV{ATI_STREAM_SDK_ROOT}/include
)

IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(OPENCL_LIB_SEARCH_PATH 
        
        # Generic
        ${OPENCL_LIB_SEARCH_PATH}
        
        # AMD
        $ENV{AMD_OPENCL}/lib/x86

        # Intel
        $ENV{INTEL_OPENCL}/lib/x86
        /usr/lib/i386-linux-gnu

        # NVIDIA
        $ENV{NVIDIA_OPENCL}/lib/x86
        $ENV{NVIDIA_GPU_COMPUTING_SDK_ROOT}/OpenCL/common/lib/Win32

        # Legacy ATI Stream SDK
        $ENV{ATI_STREAM_SDK_ROOT}/lib/x86
)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(OPENCL_LIB_SEARCH_PATH
        
        # Generic
        ${OPENCL_LIB_SEARCH_PATH}

        # AMD
        $ENV{AMD_OPENCL}/lib/x86_64

        # Intel
        $ENV{INTEL_OPENCL}/lib/x64
        /usr/lib/i386-linux-gnu

        # NVIDIA
        $ENV{NVIDIA_OPENCL}/lib/x86
        $ENV{NVIDIA_GPU_COMPUTING_SDK_ROOT}/OpenCL/common/lib/x64

        # Legacy ATI Stream SDK
        $ENV{ATI_STREAM_SDK_ROOT}/lib/x86_64
)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

# Library
FIND_LIBRARY(OPENCL_LIBRARY
    NAMES 
        OpenCL
    HINTS
        /usr/lib/x86_64-linux-gnu/
        $ENV{AMD_OPENCL}/lib/x86_64
    PATHS 
        ${OPENCL_LIB_SEARCH_PATH}
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenCL
    DEFAULT_MSG
    OPENCL_LIBRARY 
    OPENCL_INCLUDE_DIR
)

# Add the header directories to the list of include files
# Add the libraries to the list of linked libraries
IF(OPENCL_FOUND)
    MESSAGE(STATUS "OpenCL Found")
    INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})
    LINK_LIBRARIES(${OPENCL_LIBRARY})
ELSE(OPENCL_FOUND)
    MESSAGE(FATAL_ERROR "OpenCL NOT Found")
ENDIF(OPENCL_FOUND)

MARK_AS_ADVANCED(
    OPENCL_INCLUDE_DIR 
    OPENCL_LIBRARY
)
