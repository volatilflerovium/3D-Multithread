cmake_minimum_required(VERSION 3.13.4)

# Project's name
project(Multithread-3D-rotations)

FIND_PACKAGE(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# Show a message with the opencv version detected 
MESSAGE("SFML version : ${SFML_VERSION}") 

find_package (Threads)

##---------------------------------------------------
## Actual config file starts here
##--------------------------------------------------- 

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(release 0)

if(release)
	add_definitions(-DNDEBUG)
endif()

set(SOURCES
	animation.cpp
	base.cpp
	camera.cpp
	master_slave.cpp
	noise.cpp
	platonic.cpp
	shape.cpp
)

add_executable(animation-app ${SOURCES})

# link required libs
#target_link_libraries(animation-app ${SFML_LIBRARIES})

target_link_libraries(animation-app sfml-system sfml-window sfml-graphics )
target_link_libraries(animation-app ${CMAKE_THREAD_LIBS_INIT} )

# install resources
#add_subdirectory(resources)
