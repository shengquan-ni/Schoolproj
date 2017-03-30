cmake_minimum_required(VERSION 3.3.2)

project(program1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    reachable.cpp
    runoffvoting.cpp
    fa.cpp
    ndfa.cpp
    wordgenerator.cpp)
# Only new .cpp files in project; .cpp in courselib are in static library

include_directories(../courselib/)
# .hpp will be searched in . first and then in ../courselib

set(COURSELIB libcourselib.a)
# for libcourselib.a

link_directories(../courselib/)
# for both .a files

add_executable(program1 ${SOURCE_FILES})
# standard

target_link_libraries(program1 ${COURSELIB})
# .a files to link in
