################################################################################
### Copyrights (c) EPFL/BBP 2015
### Marwan Abdellah <marwanm.abdellah@epfl.ch>
################################################################################

find_package( OpenGL REQUIRED )
if( OPENGL_FOUND )
    message( STATUS "OpenGL Found" )
    include_directories( ${OPENGL_INCLUDE_DIR} )
    link_libraries( ${OPENGL_LIBRARY} )
else( OPENGL_FOUND )
    message( FATAL_ERROR "OpenGL NOT Found" )
endif( OPENGL_FOUND )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( OpenGL DEFAULT_MSG
    OPENGL_INCLUDE_DIR
    OPENGL_LIBRARY
)
