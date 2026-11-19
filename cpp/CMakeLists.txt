cmake_minimum_required(VERSION 3.16)
project(LobMatchingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(lob_core
    src/OrderBook.cpp
)
target_include_directories(lob_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lob_app src/main.cpp)
target_link_libraries(lob_app PRIVATE lob_core)

add_executable(lob_tests tests/OrderBookTest.cpp)
target_link_libraries(lob_tests PRIVATE lob_core)