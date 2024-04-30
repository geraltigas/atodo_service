include(FetchContent)

# grpc
set(ABSL_PROPAGATE_CXX_STD ON)
# PREFIX
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
        absl
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG        20240116.2
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(absl)

FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.63.0  # e.g v1.28.0
        GIT_SHALLOW TRUE
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

# sqlite3
include_directories(sqlite)
add_subdirectory(sqlite)

# gtest
#add_subdirectory(googletest)
set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

# Catch2
#FetchContent_Declare(
#  Catch2
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG        v3.5.4 # or a later release
#)
#
#FetchContent_MakeAvailable(Catch2)

# glog
#add_subdirectory(glog)
FetchContent_Declare(
        glog
        GIT_REPOSITORY https://github.com/google/glog.git
        GIT_TAG        v0.7.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glog)

# jsoncpp
FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        1.9.5
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(jsoncpp)
