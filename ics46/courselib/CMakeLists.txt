cmake_minimum_required(VERSION 3.3.2)

project(courselib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    stopwatch.cpp
    ics46goody.cpp
    ics_exceptions.cpp)

add_library(courselib STATIC ${SOURCE_FILES})
