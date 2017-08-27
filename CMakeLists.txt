cmake_minimum_required (VERSION 2.8)
project (OpenCL)

set (CMAKE_CXX_STANDARD 11) 

# Get rid of warning
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 OLD)
endif()

find_package(OpenCL REQUIRED)

include_directories( ${OpenCL_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS}/Headers )

list( APPEND SOURCES opencl-detour.cpp )

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD" )
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()
