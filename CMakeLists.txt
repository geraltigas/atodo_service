# min cmake
cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)
# set project name
project(atodo_service)

add_definitions(-DNAPI_VERSION=7)

add_subdirectory(lib)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_JS_INC})

# find all source file in src and its subdirectory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc")
include_directories("src")
include_directories("napi")

# create a var to hold all lib
set(LIBS
        sqlite
        # import glog
        glog::glog
        jsoncpp_lib
)

add_library(atodo_service ${SOURCES} ${CMAKE_JS_SRC})
set_target_properties(atodo_service PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(atodo_service ${LIBS} ${CMAKE_JS_LIB})

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()

## add test
#file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
#add_executable(atodo_service_test ${TEST_SOURCES} ${SOURCES})
#target_link_libraries(atodo_service_test ${LIBS} gtest gtest_main)
