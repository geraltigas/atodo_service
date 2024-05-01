# min cmake
cmake_minimum_required(VERSION 3.11)
# set project name
project(atodo_service)

add_subdirectory(lib)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# find all source file in src and its subdirectory
file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories("src")

# create a var to hold all lib
set(LIBS
        grpc++
        sqlite
        # import glog
        glog::glog
        jsoncpp_static
)

add_executable(atodo_service main.cpp ${SOURCES})
target_link_libraries(atodo_service ${LIBS})

# add test
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
add_executable(atodo_service_test ${TEST_SOURCES} ${SOURCES})
target_link_libraries(atodo_service_test ${LIBS} gtest gtest_main)
