cmake_minimum_required(VERSION 3.3.2)

project(program2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    driver.cpp
    test_queue.cpp
    test_priority_queue.cpp
    test_set.cpp)
# Only new .cpp files in project; .cpp in courselib are in static library

include_directories(../courselib/ ../gtestlib/include/ ../gtestlib/)
# .hpp will be searched in . first and then in these in order

set(COURSELIB libcourselib.a)
set(GTESTLIB libgtest.a)
set(GTESTLIBMAIN libgtest_main.a)
# courselib's .cpp (static libraries)

link_directories(../courselib/)
# for both .a files

add_executable(program2 ${SOURCE_FILES})
# standard

target_link_libraries(program2 ${COURSELIB} ${GTESTLIB} ${GTESTLIBMAIN})
# .a files to link in
