include(FetchContent)
set(ABSL_PROPAGATE_CXX_STD ON)
# PREFIX
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
        absl
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG        20240116.2
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(absl)

FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.63.0  # e.g v1.28.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)