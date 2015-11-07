# Application name
set( CL_FVR_APP_EXECUTABLE "clFVR" )

# Application source/header/ui files
set( CL_FVR_APP_SOURCES clFVR.cpp clFVRWindow.cpp )
set( CL_FVR_APP_HEADERS clFVRWindow.h )
set( CL_FVR_APP_FORMS clFVRWindow.ui )
qt5_wrap_ui( CL_FVR_APP_FORMS_MOC ${CL_FVR_APP_FORMS} )

# Generate the executable 
add_executable( ${CL_FVR_APP_EXECUTABLE}
    ${CL_FVR_APP_SOURCES}
    ${CL_FVR_APP_HEADERS}
    ${CL_FVR_APP_FORMS_MOC}
    ${CL_FVR_SOURCES}
    ${CL_FVR_HEADERS}
)

# Make sure to use the required Qt modules
qt5_use_modules( ${CL_FVR_APP_EXECUTABLE} Core Widgets OpenGL Gui )

# Install the executable (generate with 'make install' in the bin directory)
install( TARGETS ${CL_FVR_APP_EXECUTABLE} DESTINATION bin )

