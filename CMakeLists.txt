cmake_minimum_required(VERSION 3.2)

project(cmake VERSION 0.0.1)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(exeptional_main src/main.cpp)

add_subdirectory(gtest)
include_directories(gtest/googletest/include)
include_directories(src)

add_executable(test_exeptional test/exeptional_test.cpp)

set_target_properties(exeptional_main test_exeptional PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(test_exeptional PRIVATE gtest gmock_main)

install(TARGETS exeptional_main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(test_exeptional_tests test_exeptional)
