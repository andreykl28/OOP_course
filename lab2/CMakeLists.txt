cmake_minimum_required(VERSION 3.16)
project(lab2_variant8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(polynomial STATIC
    polynomial.cpp
    polynomial.h
)
target_include_directories(polynomial PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab2_main
    main.cpp
)
target_link_libraries(lab2_main PRIVATE polynomial)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_variant
    test_variant.cpp
)
target_link_libraries(test_variant PRIVATE polynomial GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_variant)

