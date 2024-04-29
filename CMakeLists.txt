# min cmake
cmake_minimum_required(VERSION 3.11)
# set project name
project(atodo_service)

add_subdirectory(lib)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# find all source file in src and its subdirectory
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")
include_directories("src")

# create a var to hold all lib
set(LIBS
        grpc++
        sqlite
        # import glog
        glog::glog
)

add_executable(atodo_service main.cpp ${SOURCES})
target_link_libraries(atodo_service ${LIBS})

# add test
file(GLOB TEST_SOURCES "test/*.cpp" "test/*/*.cpp")
add_executable(atodo_service_test ${TEST_SOURCES})
target_link_libraries(atodo_service_test ${LIBS} gtest gtest_main)
