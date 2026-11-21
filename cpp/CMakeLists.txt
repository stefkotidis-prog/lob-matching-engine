cmake_minimum_required(VERSION 3.16)
project(LOBMatchingEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lob_engine
    src/main.cpp
    src/OrderBook.cpp
)

target_include_directories(lob_engine PRIVATE include)
target_compile_options(lob_engine PRIVATE -Wall -Wextra -Wpedantic)