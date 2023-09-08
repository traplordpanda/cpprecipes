cmake_minimum_required(VERSION 3.27)

project(boostmp11)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# Find Boost on your system.
# "REQUIRED" will cause CMake to fail if Boost isn't found.
find_package(Boost REQUIRED json)

# FetchContent for the fmt library
include(FetchContent)
FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)
FetchContent_MakeAvailable(fmtlib)
# Specify the include directories for the compiler.
include_directories(${Boost_INCLUDE_DIRS})

add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE -Werror -Wpedantic -Wall -Wextra)

target_link_libraries(main fmt::fmt Boost::json)


