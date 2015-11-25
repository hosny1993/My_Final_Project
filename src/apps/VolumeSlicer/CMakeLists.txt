# Application name
set( VOLUME_SLICER_APP_EXECUTABLE volumeSlicer )

# Application source/header/ui files
set( VOLUME_SLICER_APP_SOURCES VolumeSlicer.cpp VolumeSlicerWindow.cpp )
set( VOLUME_SLICER_APP_HEADERS VolumeSlicerWindow.h )
set( VOLUME_SLICER_APP_FORMS VolumeSlicerWindow.ui )
qt5_wrap_ui( VOLUME_SLICER_APP_FORMS_MOC ${VOLUME_SLICER_APP_FORMS} )

# Generate the executable 
add_executable( ${VOLUME_SLICER_APP_EXECUTABLE}
    ${VOLUME_SLICER_APP_SOURCES}
    ${VOLUME_SLICER_APP_HEADERS}
    ${VOLUME_SLICER_APP_FORMS_MOC}
)

# Link the application against the CLFVR library
target_link_libraries(${VOLUME_SLICER_APP_EXECUTABLE} ${CL_FVR_LIBRARY})

# Make sure to use the required Qt modules
qt5_use_modules( ${VOLUME_SLICER_APP_EXECUTABLE} Core Widgets OpenGL Gui )

# Install the executable (generate with 'make install' in the bin directory)
install( TARGETS ${VOLUME_SLICER_APP_EXECUTABLE} DESTINATION bin )

