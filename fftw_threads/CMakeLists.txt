# Determine cmake minimum version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

# Specify project name
PROJECT( FFTW_THREADS )

# set sources files .cpp
SET(SRC_FILES "fftw_main.cpp")

# set entry point to main.cpp file
SET(ENTRY_FILE fftw_main.cpp)

# compiler option to include c++11 features
SET(CMAKE_CXX_FLAGS "-std=c++11 -lfftw3 -lfftw3_threads -lm -lpthread -g" )

# exe files
ADD_EXECUTABLE(example.x ${SRC_FILES} ${ENTRY_FILE} ${HDR_FILES})

# link requird library at runtime
TARGET_LINK_LIBRARIES(example.x fftw3 fftw3_threads pthread m)
