# min cmake
cmake_minimum_required(VERSION 3.11)
# set project name
project(atodo_service)

add_subdirectory(lib)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

add_executable(atodo_service main.cpp)
target_link_libraries(atodo_service grpc++)