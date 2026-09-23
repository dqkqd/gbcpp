cmake_minimum_required(VERSION 4.0)

project(gb CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(gb src/main.cpp)

target_compile_options(
  gb
  PRIVATE -Wall
          -Wextra
          -Wpedantic
          -Wshadow
          -Wundef
          -Wdouble-promotion
          -Wvla
          $<$<CONFIG:Release>:-O2>
          $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
