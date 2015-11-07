################################################################################
### Copyrights (c) EPFL/BBP 2015
### Marwan Abdellah <marwanm.abdellah@epfl.ch>
################################################################################

find_package( CUDA REQUIRED )

if( CUDA_FOUND )
    message( STATUS "CUDA Found" )
    include_directories( ${CUDA_INCLUDE_DIRS} )
    link_libraries( ${CUDA_LIBRARIES} )
else( CUDA_FOUND )
    message( FATAL_ERROR "CUDA NOT Found" )
endif( CUDA_FOUND )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( CUDA DEFAULT_MSG
    CUDA_INCLUDE_DIRS
    CUDA_LIBRARIES
)

### nvcc options
set( GENCODE -gencode=arch=compute_30,code=sm_30
             -gencode=arch=compute_30,code=compute_30
             -gencode=arch=compute_20,code=sm_20
             -gencode=arch=compute_20,code=compute_20
)

# Enable/disable device debugging
option( CUDA_DEVICE_DEBUGGING "On to enable debugging device code." OFF )
if( CUDA_DEVICE_DEBUGGING )
    set( DEVICE_DEBUGGING -G0 )
endif( CUDA_DEVICE_DEBUGGING )
