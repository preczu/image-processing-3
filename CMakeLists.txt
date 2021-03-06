cmake_minimum_required(VERSION 3.6)
project(image-processing)

set(CMAKE_CXX_STANDARD 11)


# To use PKG_CHECK_MODULES to find some optional packages
find_package(PkgConfig)

#    Tell CMake where to leave executables
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

#Path of CImg.h file relative to this file path
set(CIMG_H_PATH ${PROJECT_SOURCE_DIR}/libs/)
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${CIMG_H_PATH} )


if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()

if (NOT WIN32)
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if( WIN32)
    SET( SYSTEM_LIBS  ${SYSTEM_LIBS}  gdi32 )
endif()


include_directories(src)
include_directories(src/modifications)
include_directories(lib)

add_executable(image-processing
        src/main.cpp
        src/modifications/RegionGrow.cpp src/modifications/RegionGrow.h)
target_link_libraries(image-processing ${SYSTEM_LIBS})



